//
//  HistogramOrientedGradient.cpp
//  Competition
//
//  Created by Rafael Vareto on 11/7/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#include "HistogramOrientedGradient.hpp"

HistogramOrientedGradient::HistogramOrientedGradient(
                                                     const cv::Size &_block,
                                                     const cv::Size &_stride,
                                                     const cv::Size &_cell)
: block(_block), cell(_cell), stride(_stride) {
    
}

HistogramOrientedGradient::~HistogramOrientedGradient() {
    
}

pair<int,int> HistogramOrientedGradient::getBlockSize() {
    return pair<int,int>(this->block.width, this->block.height);
}

Matrix HistogramOrientedGradient::run(const Image &_image) const {
    Matrix features;
    std::vector<float> hogDescriptor;
    Image temp = _image.clone();
    vector<cv::Point> points;
    
//    cv::HOGDescriptor hog(
//                          cv::Size(_image.cols, _image.rows), // window
//                          this->block,  // block
//                          this->stride, // stride
//                          this->cell,   // cell
//                          9,            // bins
//                          1,
//                          -1,
//                          cv::HOGDescriptor::L2Hys,
//                          0.4
//                          );
//    hog.compute(_image, hogDescriptor);
    //cv::cvtColor(_image, temp, CV_RGB2GRAY);
    
    cv::HOGDescriptor hog;
    hog.winSize = cv::Size(std::min(_image.rows, _image.cols), std::min(_image.rows, _image.cols));
    hog.compute(temp, hogDescriptor, cv::Size(16,16), cv::Size(0,0), points);
    
    features = cv::Mat(1, hogDescriptor.size(), CV_32F, hogDescriptor.data());
    //cv::Mat(hogDescriptor, true).convertTo(features, CV_32F);
    
    return features;
}