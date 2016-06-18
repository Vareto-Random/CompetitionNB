//
//  Useful.cpp
//  Competition
//
//  Created by Rafael Vareto on 11/7/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#include "Useful.hpp"

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