//
//  ImageSet.cpp
//  Competition
//
//  Created by Rafael Vareto on 10/22/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#include "Collection.hpp"

Collection::Collection() {
    this->setUpBoolValues(false);
}

Collection::Collection(const map<string, cv::Mat> &_imageArray) {
    this->setUpBoolValues(false);
    this->setImageArray(_imageArray);
}

Collection::Collection(const Collection &_collection) {
    this->cellArray = _collection.cellArray;
    this->componentArray = _collection.componentArray;
    this->faceArray = _collection.faceArray;
    this->imageArray = _collection.imageArray;
    
    this->setUpBoolValues(true);
}

Collection::~Collection() {
}

bool Collection::blurFaces(const int _size, const int _sigma, bool _show) {
    map<string, cv::Mat>::iterator it;
    for (it = this->imageArray.begin(); it != this->imageArray.end(); it++) {
        cv::Mat *image = &(it->second);
        cv::GaussianBlur(*image, *image, cv::Size(_size,_size), _sigma);
        
        if (_show) {
            cv::imshow("negative", *image);
            cv::waitKey();
        }
    }
    return false;
}

bool Collection::resizeFaces(const int _size = 256) {
    if (_size > 0) {
        map<string, cv::Mat>::iterator it;
        for (it = this->imageArray.begin(); it != this->imageArray.end(); it++) {
            cout << it->first << ": " << it->second.rows << " - " << it->second.cols << endl;
            cv::resize(it->second, it->second, cv::Size(_size, _size));
        }
        return true;
    }
    return false;
}

bool Collection::sharpenFaces() {
    map<string, cv::Mat>::iterator it;
    for (it = this->imageArray.begin(); it != this->imageArray.end(); it++) {
        cv::Mat temp;
        cv::GaussianBlur(it->second, temp, cv::Size(9,9), 5);
        cv::addWeighted(it->second, 1.5, temp, -0.5, 0, it->second);
    }
    return true;
}

bool Collection::fetchCells(bool _show) {
    assert(this->imageArray.size() == this->cellArray.size());
    
    vector<Descriptor *> descriptors;
    descriptors.push_back(new CompoundLocalBinaryPattern(12, cv::Size(50,50), cv::Size(24,24)));
    //descriptors.push_back(new HistogramOrientedGradient);
    //*descriptors.push_back(new PatternOrientedEdgeMagnitude);
    //descriptors.push_back(new LocalBinaryPattern(cv::Size(36,30), cv::Size(24,20)));
    //descriptors.push_back(new PatternOrientedEdgeMagnitude(3, 7, cv::Size(8,8), cv::Size(32,32), cv::Size(16,16)));
    
    map<string, cv::Mat>::iterator itImage;
    map<string, vector<Cell> >::iterator itLand;
    
    for (itImage = this->imageArray.begin(), itLand = this->cellArray.begin();
         itImage != this->imageArray.end() and itLand != this->cellArray.end();
         itImage++, itLand++) {
        
        cv::Mat *image = &(itImage->second);
        for(int outer = 0; outer < itLand->second.size(); outer++) {
            Cell *cell = &(itLand->second[outer]);
            
            for (int inner = 0; inner < descriptors.size(); inner++) {
                (*cell).setBlockWidth(2 * descriptors[inner]->getBlockSize().first);
                (*cell).setBlockHeight(2 * descriptors[inner]->getBlockSize().second);
                cv::Mat patch(*image, cv::Rect(cell->getX0(), cell->getY0(), cell->getBlockWidth(), cell->getBlockHeight()));
                cell->setFeature(patch, (*descriptors[inner]));
//                cout << outer << ":" << inner << endl;
            }
            
            if (_show) {
                cout << itImage->first << " - " << outer << endl;
                cv::rectangle(*image, cv::Rect(cell->getX0(), cell->getY0(), cell->getBlockWidth(), cell->getBlockHeight()), cv::Scalar(0, 0, 255), 1);
                cv::imshow("subject", *image);
                cv::waitKey();
            }
        }
    }
    
    this->cellStatus = true;
    return true;
}

bool Collection::fetchComponents(bool _show) {
    assert(this->imageArray.size() == this->cellArray.size());
    int height, width;
    
    vector<Descriptor *> descriptors;
    descriptors.push_back(new CompoundLocalBinaryPattern(8, cv::Size(54,54), cv::Size(24,24)));
    //descriptors.push_back(new HistogramOrientedGradient);
    //descriptors.push_back(new GaborFilter);
    //descriptors.push_back(new PatternOrientedEdgeMagnitude);
    //descriptors.push_back(new LocalBinaryPattern(cv::Size(32,32), cv::Size(16,16)));
    //descriptors.push_back(new LocalBinaryPattern(cv::Size(75,75), cv::Size(25,25)));
    //descriptors.push_back(new PatternOrientedEdgeMagnitude(3, 7, cv::Size(8,8), cv::Size(32,32), cv::Size(16,16)));
    
    map<string, cv::Mat>::iterator itImage;
    map<string, vector<Cell> >::iterator itLand;
    
    for (itImage = this->imageArray.begin(), itLand = this->cellArray.begin();
         itImage != this->imageArray.end() and itLand != this->cellArray.end();
         itImage++, itLand++) {
        
        vector<Component> components;
        cv::Mat *matrix = &(itImage->second);
        
        //left eyebrow: 0 to 5
        Component lEyebrow;
        lEyebrow.setX( itLand->second[0].getX() - SHIFT );
        lEyebrow.setY( itLand->second[2].getY() - SHIFT );
        lEyebrow.setBlockWidth( itLand->second[4].getX() -  itLand->second[0].getX() );
        lEyebrow.setBlockHeight( max(itLand->second[0].getY(), itLand->second[4].getY()) -  itLand->second[2].getY() );
        lEyebrow.setName("lEyebrow");
        components.push_back(lEyebrow);
        
        //right eyebrow: 5 to 9
        Component rEyebrow;
        rEyebrow.setX( itLand->second[5].getX() - SHIFT );
        rEyebrow.setY( itLand->second[7].getY() - SHIFT );
        rEyebrow.setBlockWidth( itLand->second[9].getX() -  itLand->second[5].getX() );
        rEyebrow.setBlockHeight( max(itLand->second[5].getY(), itLand->second[9].getY()) -  itLand->second[7].getY() );
        rEyebrow.setName("rEyebrow");
        components.push_back(rEyebrow);
        
        //nose: 10 to 18
        Component nose;
        nose.setX( itLand->second[14].getX() - SHIFT );
        nose.setY( itLand->second[10].getY() - SHIFT );
        nose.setBlockWidth( itLand->second[18].getX() -  itLand->second[14].getX() + (2 * SHIFT) );
        nose.setBlockHeight( itLand->second[16].getY() -  itLand->second[10].getY() + (2 * SHIFT) );
        nose.setName("nose");
        components.push_back(nose);
        
        //left eye: 19 to 24
        Component lEye;
        lEye.setX( itLand->second[19].getX() - SHIFT );
        lEye.setY( min(itLand->second[20].getY(), itLand->second[21].getY()) - SHIFT );
        lEye.setBlockWidth( itLand->second[22].getX() -  itLand->second[19].getX() + (2 * SHIFT) );
        lEye.setBlockHeight( max(itLand->second[23].getY(), itLand->second[24].getY()) -  min(itLand->second[20].getY(), itLand->second[21].getY()) + (2 * SHIFT) );
        lEye.setName("lEye");
        components.push_back(lEye);
        
        //right eye: 25 to 30
        Component rEye;
        rEye.setX( itLand->second[25].getX() - SHIFT );
        rEye.setY( min(itLand->second[26].getY(), itLand->second[27].getY()) - SHIFT );
        rEye.setBlockWidth( itLand->second[28].getX() -  itLand->second[25].getX() + (2 * SHIFT) );
        rEye.setBlockHeight( max(itLand->second[29].getY(), itLand->second[30].getY()) -  min(itLand->second[26].getY(), itLand->second[27].getY()) + (2 * SHIFT) );
        rEye.setName("rEye");
        components.push_back(rEye);
        
        //mouth: 31 to 50
        Component mouth;
        mouth.setX( itLand->second[31].getX() - SHIFT );
        mouth.setY( min(itLand->second[33].getY(), itLand->second[35].getY()) - SHIFT );
        mouth.setBlockWidth( itLand->second[37].getX() -  itLand->second[31].getX() + (2 * SHIFT) );
        mouth.setBlockHeight( itLand->second[40].getY() -  min(itLand->second[33].getY(), itLand->second[35].getY()) + (2 * SHIFT) );
        mouth.setName("mouth");
        components.push_back(mouth);
        
        //        //both eyes
        //        Component bothEyes;
        //        bothEyes.setX( itLand->second[19].getX() - SHIFT );
        //        bothEyes.setY( min(itLand->second[20].getY(), itLand->second[27].getY()) - SHIFT );
        //        bothEyes.setBlockWidth( itLand->second[28].getX() -  itLand->second[19].getX() + (2 * SHIFT) );
        //        bothEyes.setBlockHeight( max(itLand->second[24].getY(), itLand->second[30].getY()) -  min(itLand->second[20].getY(), itLand->second[27].getY()) + (2 * SHIFT) );
        //        components.push_back(bothEyes);
        
        for (int outer = 0; outer < components.size(); outer++) {
            cv::Mat patch(*matrix, cv::Rect(components[outer].getX(), components[outer].getY(), components[outer].getBlockWidth(), components[outer].getBlockHeight()));
            
            if (components[outer].getName() == "lEyebrow") {
                height = 24;
                width = 72;
            } else if (components[outer].getName() == "rEyebrow") {
                height = 24;
                width = 72;
            } else if (components[outer].getName() == "nose") {
                height = 56;
                width = 84;
            } else if (components[outer].getName() == "lEye") {
                height = 32;
                width = 56;
            } else if (components[outer].getName() == "rEye") {
                height = 32;
                width = 56;
            } else if (components[outer].getName() == "mouth") {
                height = 48;
                width = 96;
            }
            
            for (int inner = 0; inner < descriptors.size(); inner++) {
                cv::Size size = cv::Size(width, height);
                cv::resize(patch, patch, size);
                
                if(patch.channels() > 1) {
                    cv::cvtColor(patch, patch, CV_RGB2GRAY);
                }
                components[outer].setFeature(patch, *descriptors[inner]);
            }
        }
        
        if (_show) {
            cv::rectangle(*matrix, cv::Rect(lEyebrow.getX(), lEyebrow.getY(), lEyebrow.getBlockWidth(), lEyebrow.getBlockHeight()), cv::Scalar(0, 0, 255), 1);
            cv::rectangle(*matrix, cv::Rect(rEyebrow.getX(), rEyebrow.getY(), rEyebrow.getBlockWidth(), rEyebrow.getBlockHeight()), cv::Scalar(0, 0, 255), 1);
            cv::rectangle(*matrix, cv::Rect(nose.getX(), nose.getY(), nose.getBlockWidth(), nose.getBlockHeight()), cv::Scalar(0, 0, 255), 1);
            cv::rectangle(*matrix, cv::Rect(lEye.getX(), lEye.getY(), lEye.getBlockWidth(), lEye.getBlockHeight()), cv::Scalar(0, 0, 255), 1);
            cv::rectangle(*matrix, cv::Rect(rEye.getX(), rEye.getY(), rEye.getBlockWidth(), rEye.getBlockHeight()), cv::Scalar(0, 0, 255), 1);
            cv::rectangle(*matrix, cv::Rect(mouth.getX(), mouth.getY(), mouth.getBlockWidth(), mouth.getBlockHeight()), cv::Scalar(0, 0, 255), 1);
            // cv::rectangle(*matrix, cv::Rect(bothEyes.getX(), bothEyes.getY(), bothEyes.getBlockWidth(), bothEyes.getBlockHeight()), cv::Scalar(0, 255, 255), 1);
            cv::imshow("subject", *matrix);
            cv::waitKey();
        }
        
        this->componentArray.insert( pair<string, vector<Component> >(itLand->first, components) );
        components.clear();
    }
    
    this->componentStatus = true;
    return true;
}

bool Collection::fetchFaces(bool _show) {
    vector<Descriptor *> descriptors;
    descriptors.push_back(new CompoundLocalBinaryPattern);
    //descriptors.push_back(new HistogramOrientedGradient);
    //*descriptors.push_back(new LocalBinaryPattern);
    //descriptors.push_back(new PatternOrientedEdgeMagnitude);
    //descriptors.push_back(new CompoundLocalBinaryPattern(12, cv::Size(50,50), cv::Size(24,24)));
    //descriptors.push_back(new LocalBinaryPattern(cv::Size(36,30), cv::Size(24,20)));
    //descriptors.push_back(new PatternOrientedEdgeMagnitude(3, 7, cv::Size(8,8), cv::Size(32,32), cv::Size(16,16)));
    
    map<string, cv::Mat>::iterator itImage;
    
    for (itImage = this->imageArray.begin(); itImage != this->imageArray.end(); itImage++) {
        cv::Mat *image = &(itImage->second);
        Face face;
        
        for (int index = 0; index < descriptors.size(); index++) {
            face.setFeature(*image, *descriptors[index]);
        }
        
        this->faceArray.insert( pair<string, Face>(itImage->first, face) );
        face.clear();
        
        if (_show) {
            cout << itImage->first << endl;
            cv::imshow("subject", *image);
            cv::waitKey();
        }
    }

    this->faceStatus = true;
    return true;
}

/*
 * get the shape_predictor_68_face_landmarks.dat file from
 * http://dlib.net/files/shape_predictor_68_face_landmarks.dat.bz2
 */
bool Collection::fetchLandmarks(const string &_model, bool _show) {
    dlib::shape_predictor model;
    dlib::deserialize(_model) >> model;
    vector<Cell> points;
    
    map<string, cv::Mat>::iterator it;
    for(it = this->imageArray.begin(); it != this->imageArray.end(); it++) {
        dlib::cv_image<dlib::bgr_pixel> image(it->second);
        dlib::rectangle face = dlib::get_rect(image);
        dlib::full_object_detection landmark = model(image, face);
        
        //discard face shape fiducial points
        //cout << "Subject " << it->first << "\n";
        for (int index = 17; index < landmark.num_parts(); index++) {
            //cout << landmark.part(index).x() << " " << landmark.part(index).y() << "\n";
            points.push_back( Cell(landmark.part(index).x(), landmark.part(index).y(), it->second.size()) );
        }
        
        this->cellArray.insert(pair< string, vector<Cell> >(it->first, points));
        
        if(_show) {
            dlib::image_window window;
            window.clear_overlay();
            window.set_image(image);
            window.add_overlay(dlib::render_face_detections(landmark));
            cin.get();
        }
        points.clear();
    }
    
    return false;
}

map<string, vector<Cell> > Collection::getCellArray() {
    return this->cellArray;
}

map<string, vector<Component> > Collection::getComponentArray() {
    return this->componentArray;
}

map<string, Face> Collection::getFaceArray() {
    return this->faceArray;
}

map<string, cv::Mat> Collection::getImageArray() {
    return this->imageArray;
}

bool Collection::getAllFeatures(Matrix &_samples) {
    Labels labels;
    return this->getAllFeatures(_samples, labels, false);
}

bool Collection::getAllFeatures(Matrix &_samples, Labels &_labels, const bool _extra) {  
    int count = _labels.size();
    _labels.resize(_labels.size() + this->cellArray.size());
    
    vector<string> compare;
    
    // Loop at all samples
    map<string, vector<Cell> >::iterator itCell;
    map<string, vector<Component> >::iterator itComp;
    map<string, Face>::iterator itFace;
    for (itCell = this->cellArray.begin(), itComp = this->componentArray.begin()/*, itFace = this->faceArray.begin()*/;
         itCell != this->cellArray.end() or itComp != this->componentArray.end() /*or itFace != this->faceArray.end()*/;
         itCell++, itComp++/*, itFace++*/) {
        
        cv::Mat sample;
        _labels[count].setId(itCell->first.substr(0,3));
        _labels[count].setExtra(_extra);

        if (this->cellStatus) {
            assert(this->imageArray.size() == this->cellArray.size());
            compare.push_back(itCell->first);
            // Loop at all cells
            for(int outer = 0; outer < itCell->second.size(); outer++) {
                Cell *cell = &(itCell->second[outer]);
                vector<Matrix> features = (*cell).getFeatures();
                // Loop at all features
                for (int inner = 0; inner < features.size(); inner++) {
                    if(sample.empty()) {
                        sample = features[inner].clone();
                    } else {
                        cv::hconcat(sample, features[inner], sample);
                    }
                }
            }
        }
        
        if (this->componentStatus) {
            assert(this->imageArray.size() == this->componentArray.size());
            compare.push_back(itComp->first);
            // Loop at all components
            for (int outer = 0; outer < itComp->second.size(); outer++) {
                Component *component = &(itComp->second[outer]);
                vector<Matrix> features = (*component).getFeatures();
                // Loop at all features
                for (int inner = 0; inner < features.size(); inner++) {
                    if(sample.empty()) {
                        sample = features[inner].clone();
                    } else {
                        cv::hconcat(sample, features[inner], sample);
                    }
                }
            }
        }
        
        if (this->faceStatus) {
            assert(this->imageArray.size() == this->faceArray.size());
            compare.push_back(itFace->first);
            // Loop at all faces
            Face *face = &(itFace->second);
            vector<Matrix> features = (*face).getFeatures();
            
            for (int index = 0; index < features.size(); index++) {
                if(sample.empty()) {
                    sample = features[index].clone();
                } else {
                    cv::hconcat(sample, features[index], sample);
                }
            }
        }

        //cout << compare.size() << ": ";
        //for (int index = 0; index < compare.size(); index++) {
        //    cout << compare[index] << " ";
        //}
        //cout << endl;
        
        //Check if samples names match
        for (int index = 0; index < compare.size() - 1; index++) {
            assert(compare[index] == compare[index+1]);
        }
        compare.clear();
        
        _samples.push_back(sample);
        count++;
    }
    return true;
}

bool Collection::getComponentsFeatures(vector<Matrix> &_samples) {
    Labels labels;
    return this->getComponentsFeatures(_samples, labels, false);
}

bool Collection::getComponentsFeatures(vector<Matrix> &_samples, Labels &_labels, const bool _extra) {
    assert( this->cellArray.size() and this->componentArray.size() );
    
    int count = _labels.size();
    _labels.resize(_labels.size() + this->cellArray.size());
    _samples.resize(this->componentArray.begin()->second.size());
    
    //Loop at all samples
    map<string, vector<Component> >::iterator it;
    for (it = this->componentArray.begin(); it != this->componentArray.end(); it++) {
        
        cv::Mat sample;
        _labels[count].setId(it->first.substr(0,3));
        _labels[count].setExtra(_extra);
        //cout << _labels[count].getId() << endl;
        
        // Loop at all components
        for (int outer = 0; outer < it->second.size(); outer++) {
            Component *component = &(it->second[outer]);
            vector<Matrix> features = component->getFeatures();
            
            // Loop at all features
            for (int inner = 0; inner < features.size(); inner++) {
                if(sample.empty()) {
                    sample = features[inner].clone();
                } else {
                    cv::hconcat(sample, features[inner], sample);
                }
            }
            
            //cout << "\t" << it->first << " - " << sample.cols << " " << sample.rows << endl;
            _samples[outer].push_back(sample);
            sample.release();
        }
        count++;
    }
    
    return true;
}

bool Collection::getFacesFeatures(Matrix &_samples, Labels &_labels, const bool _extra) {
    int count = _labels.size();
    _labels.resize(_labels.size() + this->faceArray.size());
    
    // Loop at all samples
    map<string, Face>::iterator it;
    for (it = this->faceArray.begin(); it != faceArray.end(); it++) {
        Face *face = &(it->second);
        vector<Matrix> features = (*face).getFeatures();
        
        cv::Mat sample;
        _labels[count].setId(it->first.substr(0,3));
        _labels[count].setExtra(_extra);
        
        // Loop at all features
        for (int index = 0; index < features.size(); index++) {
            if(sample.empty()) {
                sample = features[index].clone();
            } else {
                cv::hconcat(sample, features[index], sample);
            }
        }
        
        _samples.push_back(sample);
        count++;
    }
    
    return true;
}

bool Collection::setImageArray(const map<string, cv::Mat> &_imageArray) {
    if (_imageArray.size() > 0) {
        this->imageArray = _imageArray;
        return true;
    }
    return false;
}

/*
 * Private Methods
 */

void Collection::setUpBoolValues(bool _value) {
    this->cellStatus = _value;
    this->componentStatus = _value;
    this->faceStatus = _value;
}
