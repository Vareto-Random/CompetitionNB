//
//  LocalBinaryPattern.cpp
//  Competition
//
//  Created by Rafael Vareto on 11/7/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#include "LocalBinaryPattern.hpp"

LocalBinaryPattern::LocalBinaryPattern(
                                       const cv::Size &_block,
                                       const cv::Size &_stride
                                       )
: block(_block), stride(_stride) {
    
}

LocalBinaryPattern::~LocalBinaryPattern() {
    
}

pair<int,int> LocalBinaryPattern::getBlockSize() {
    return pair<int,int>(this->block.width, this->block.height);
}

Matrix LocalBinaryPattern::run(const Image &_image) const {
    Matrix descriptor;
    
    cv::Mat gray;
    cv::cvtColor(_image, gray, CV_BGR2GRAY);
    
    Image lbp_image = Image::zeros(gray.rows - 2, gray.cols - 2, CV_32F);
    
    for (int i = 1; i < gray.rows - 1; i++) {
        for (int j = 1; j < gray.cols - 1; j++) {
            uchar center = gray.at<uchar>(i, j);
            unsigned char code = 0;
            code |= (gray.at<uchar>(i - 1, j - 1) > center) << 7;
            code |= (gray.at<uchar>(i - 1, j) > center) << 6;
            code |= (gray.at<uchar>(i - 1, j + 1) > center) << 5;
            code |= (gray.at<uchar>(i, j + 1) > center) << 4;
            code |= (gray.at<uchar>(i + 1, j + 1) > center) << 3;
            code |= (gray.at<uchar>(i + 1, j) > center) << 2;
            code |= (gray.at<uchar>(i + 1, j - 1) > center) << 1;
            code |= (gray.at<uchar>(i, j - 1) > center) << 0;
            lbp_image.at<float>(i - 1, j - 1) = code;
        }
    }
    
    const int channels[] = { 0 };
    const int histSize[] = { 255 };
    const float range[] = { 0, 256 };
    const float* ranges[] = { range };
    
    cv::Size _block = block;
    if(_block.width > lbp_image.cols)
        _block.width = lbp_image.cols;
    if(_block.height > lbp_image.rows)
        _block.height = lbp_image.rows;
    
    SlideWindow::slideWindow(lbp_image, _block, this->stride, [&](Image & crop) {
        cv::Mat hist;
        cv::calcHist(&crop, 1, channels, cv::Mat(),
                     hist, 1, histSize, ranges, true, false);
        hist.convertTo(hist, CV_32F);
        hist = hist.reshape(1, 1);
        hist /= cv::sum(hist)[0];
        descriptor.cbind(hist);
    });
    
    return descriptor;
}