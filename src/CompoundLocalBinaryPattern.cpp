//
//  CompoundLocalBinaryPattern.cpp
//  Competition
//
//  Created by Rafael Vareto on 11/7/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#include "CompoundLocalBinaryPattern.hpp"

CompoundLocalBinaryPattern::CompoundLocalBinaryPattern(
                                                       const int _radius,
                                                       const cv::Size &_block,
                                                       const cv::Size &_stride)
: radius(_radius), block(_block), stride(_stride) {
    
}

CompoundLocalBinaryPattern::~CompoundLocalBinaryPattern() {
    
}

pair<int,int> CompoundLocalBinaryPattern::getBlockSize() {
    return pair<int,int>(this->block.width, this->block.height);
}

Matrix CompoundLocalBinaryPattern::run(const Image &_image) const {
    Matrix descriptor;
    
    Image gray;
    if (_image.channels() > 1) {
        cv::cvtColor(_image, gray, CV_BGR2GRAY);
    } else {
        gray = _image.clone();
    }
    return structure<uchar>(gray, descriptor);
}