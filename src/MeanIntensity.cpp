//
//  MeanIntensity.cpp
//  Competition
//
//  Created by Rafael Vareto on 11/7/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#include "MeanIntensity.hpp"

MeanIntensity::MeanIntensity(
                             const cv::Size &_block,
                             const cv::Size &_stride)
: block(_block), stride(_stride) {
    
}

MeanIntensity::~MeanIntensity() {
    
}

pair<int,int> MeanIntensity::getBlockSize() {
    return pair<int,int>(this->block.width, this->block.height);
}

Matrix MeanIntensity::run(const Image &_image) const {
    Matrix features;
    SlideWindow::slideWindow(_image, this->block, this->stride, [&](Image & crop) {
        Matrix val(1, 1);
        cv::cvtColor(crop, crop, CV_RGB2GRAY);
        val = cv::mean(crop)[0];
        features.cbind(val);
    });
    
    return features;
}