//
//  Useful.cpp
//  Competition
//
//  Created by Rafael Vareto on 11/7/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#include "Useful.hpp"
#include "Annotation.hpp"

void Useful::gradient(const Image &_image, Matrix &_orientation, Matrix &_magnitude) {
    Image gray;
    cv::cvtColor(_image, gray, CV_RGB2BGR);

    static float kernel[] = {-1, 0, 1};
    static cv::Mat_<float> hkernel(1, 3, kernel), vkernel(3, 1, kernel);

    Image himage, vimage;
    cv::filter2D(gray, himage, -1, hkernel);
    cv::filter2D(gray, vimage, -1, vkernel);

    assert(gray.cols == himage.cols && gray.rows == himage.rows);
    assert(gray.cols == vimage.cols && gray.rows == vimage.rows);

    _orientation.create(gray.rows, gray.cols);
    _magnitude.create(gray.rows, gray.cols);

    for (int row = 0; row < gray.rows; ++row) {

        for (int col = 0; col < gray.cols; ++col) {

            float o;
            if (himage.at<uchar>(row, col) == 0 &&
                    vimage.at<uchar>(row, col) == 0)
                o = 0;
            else
                o = atan(
                    himage.at<uchar>(row, col) /
                    (float) vimage.at<uchar>(row, col));
            float m = sqrt(
                    himage.at<uchar>(row, col) * himage.at<uchar>(row, col) +
                    vimage.at<uchar>(row, col) * vimage.at<uchar>(row, col));

            _orientation(row, col) = o;
            _magnitude(row, col) = m;
        }
    }
}

void Useful::save2file(const PLSclassifier &_model, const Matrix &_responses, const Labels &_probeLabels) {
    ofstream output;
    output.open("similarityScore.csv");

    cout << "\t_responses (rows:cols) = (" << _responses.rows << ":" << _responses.cols << ")\n";

    for (int outer = 0; outer < _responses.rows; outer++) {
        Matrix response = _responses.row(outer);

        for (int inner = 0; inner < response.cols; inner++) {
            output << response(inner) << "\t";
        }

        output << "\n";
    }

    output.close();
}

vector<string> Useful::readCNNfeatures(const string &_featurePath, const string &_notePath, cv::Mat &_featureMatrix, Labels &_featureLabels) {
    ifstream inFeature, inLabels;
    set<string> subjects;

    inLabels.open(_notePath, ifstream::in);
    if (inLabels.is_open()) {
        Annotation data;
        vector<Annotation> dataArray;
        
        while (inLabels.good()) {
            inLabels >> data.file;
            inLabels >> data.posX;
            inLabels >> data.posY;
            inLabels >> data.width;
            inLabels >> data.height;
            
            subjects.insert(data.file.substr(0, 3));
            dataArray.push_back(data);
            // cout << data.file.substr(0, 3) << " ";
        }
        
        _featureLabels.resize(dataArray.size());
        for (unsigned int index = 0; index < _featureLabels.size(); index++) {
            _featureLabels[index].setId(dataArray[index].file.substr(0, 3));
            _featureLabels[index].setExtra(false);
        }
        // cout << endl << "Size: " << _featureLabels.size() << endl;
    } else {
        cerr << "You have inserted the wrong path to the CNN annotation file" << endl;
    }
    inLabels.close();

    inFeature.open(_featurePath, ifstream::in);
    if (inFeature.is_open()) {
        float feature;
        vector<float> features;
        while (inFeature.good()) {
            inFeature >> feature;
            features.push_back(feature);
        }
        
        // cout << "COUNTER: " << features.size() << "\n |features(:)|/|FeatureLabels|: " << features.size() / _featureLabels.size() << endl;
        
        int rows = _featureLabels.size();
        int cols = features.size() / _featureLabels.size();
        cv::Mat featuresMat(rows, cols, CV_32F, &features[0]);
        _featureMatrix = featuresMat.clone();
        
//        for (unsigned int outer = 0; outer < _featureMatrix.rows; outer++) {        
//            for (unsigned int inner = 0; inner < _featureMatrix.cols; inner++) {
//                cout << _featureMatrix.row(outer).col(inner) << " ";
//            }
//            cin.get();
//        }
        
        featuresMat.release();
        
    } else {
        cerr << "You have inserted the wrong path to the CNN feature file" << endl;
    }
    inFeature.close();
    
    return vector<string>(subjects.begin(), subjects.end());
}