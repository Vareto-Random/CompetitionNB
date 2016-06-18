//
//  ImageSet.cpp
//  Competition
//
//  Created by Rafael Vareto on 10/22/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#include "ImageSet.hpp"

ImageSet::ImageSet() {
    this->runFile = false;
    this->runPath = false;
}

ImageSet::ImageSet(const string &_file, const string &_path) {
    this->runFile = true;
    this->runPath = true;
    
    this->file = _file;
    this->path = _path;
}

ImageSet::ImageSet(const ImageSet &_imageSet) {
    this->dataArray = _imageSet.dataArray;
    this->path = _imageSet.path;
    this->runFile = _imageSet.runFile;
    this->runPath = _imageSet.runPath;
}

ImageSet::~ImageSet() {
}

void ImageSet::setFile(string &_file) {
    this->file = _file;
    this->runFile = true;
}

void ImageSet::setPath(string &_path) {
    this->path = _path;
    this->runPath = true;
}

bool ImageSet::increaseWindowSize(const double _percent) {
    if(_percent >= 1.0) {
        int hGap, wGap;
        for (int index = 0; index < this->dataArray.size(); index++) {
            Annotation notes = this->dataArray[index];
            notes.height = (int) notes.height * _percent;
            notes.width = (int) notes.width * _percent;
            hGap = (int) std::abs(notes.height - this->dataArray[index].height) / 2;
            wGap = (int) std::abs(notes.width - this->dataArray[index].width) / 2;
            notes.posY -= hGap;
            notes.posX -= wGap;
            
            this->dataArray[index] = notes;
        }
        return true;
    }
    return false;
}

bool ImageSet::loadFaces(const bool _crop) {
    if(this->runFile && this->runPath && (this->dataArray.size() > 0)) {
        return this->loadFaces(this->dataArray, this->path, _crop);
    }
    return false;
}

bool ImageSet::loadFaces(const string &_filter, const bool _crop) {
    if(this->runFile && this->runPath && (this->dataArray.size() > 0)) {
        return this->loadFaces(this->dataArray, this->path, _filter, _crop);
    }
    return false;
}

// Private Method
bool ImageSet::loadFaces(const vector<Annotation> &_dataArray, const string &_path, const bool _crop) {
    bool status = true;
    
    for (int index = 0; index < _dataArray.size(); index++) {
        Annotation notes = _dataArray[index];
        
        try {
            cv::Mat image = cv::imread(_path + notes.file);
            
            if (_crop) {
                if (notes.posX + notes.width > image.cols) {
                    notes.posX = image.cols - notes.width;
                }
                if (notes.posY + notes.height > image.rows) {
                    notes.posY = image.rows - notes.height;
                }
                
                cv::Mat crop = image(cv::Rect(notes.posX, notes.posY, notes.width, notes.height)).clone();
                this->imageArray.insert(pair<string,cv::Mat>(notes.file, crop));
                image.release();
            } else {
                this->imageArray.insert(pair<string,cv::Mat>(notes.file, image));
            }
        } catch (cv::Exception ex) {
            status = false;
            cerr << notes.file + " could NOT be read. It might be the wrong path.\n";
        }
    }
    return status;
}

// Private Method
bool ImageSet::loadFaces(const vector<Annotation> &_dataArray, const string &_path, const string &_filter, const bool _crop) {
    bool status = true;
    
    for (int index = 0; index < _dataArray.size(); index++) {
        Annotation notes = _dataArray[index];
        
        if (notes.file.find(_filter) != string::npos) {
            try {
                cv::Mat image = cv::imread(_path + notes.file, CV_LOAD_IMAGE_GRAYSCALE);
                
                if (_crop) {
                    if (notes.posX + notes.width > image.cols) {
                        notes.posX = image.cols - notes.width;
                    }
                    if (notes.posY + notes.height > image.rows) {
                        notes.posY = image.rows - notes.height;
                    }
                    
                    cv::Mat crop = image(cv::Rect(notes.posX, notes.posY, notes.width, notes.height)).clone();
                    image.release();
                    this->imageArray.insert(pair<string,cv::Mat>(notes.file,crop));
                } else {
                    this->imageArray.insert(pair<string,cv::Mat>(notes.file,image));
                }
            } catch (cv::Exception ex) {
                status = false;
                cerr << notes.file + " could NOT be read. It might be the wrong path.\n";
            }
        }
    }
    return status;
}

bool ImageSet::readNotes(const bool _crop) {
    if (this->runFile) {
        return this->readNotes(this->file, _crop);
    }
    return false;
}

bool ImageSet::readNotes(const string &_file, const bool _crop) {
    Annotation data;
    ifstream infile(_file, ifstream::in);
    
    if (infile.is_open()) {
        while (infile.good()) {
            infile >> data.file;
            if (_crop) {
                infile >> data.posX;
                infile >> data.posY;
                infile >> data.width;
                infile >> data.height;
            } else {
                data.posX = -1;
                data.posY = -1;
                data.width = -1;
                data.height = -1;
            }
            this->samples.insert(data.file);
            this->subjects.insert(data.file.substr(0,3));
            this->dataArray.push_back(data);
        }
        return true;
    }
    return false;
}

set<string> ImageSet::getSamplesSet() {
    return this->samples;
}

set<string> ImageSet::getSubjectsSet() {
    return this->subjects;
}

vector<string> ImageSet::getSamples() {
    vector<string> result;
    
    set<string>::iterator it;
    for (it = this->samples.begin(); it != this->samples.end(); it++) {
        result.push_back(*it);
    }
    
    return result;
}

vector<string> ImageSet::getSubjects() {
    vector<string> result;
    
    set<string>::iterator it;
    for (it = this->subjects.begin(); it != this->subjects.end(); it++) {
        result.push_back(*it);
    }
    
    return result;
}

vector<Annotation> ImageSet::getDataArray() {
    return this->dataArray;
}

map<string, cv::Mat> ImageSet::getImageArray() {
    return this->imageArray;
}