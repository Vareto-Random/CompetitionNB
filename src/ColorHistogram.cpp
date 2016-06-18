//
//  ColorHistogram.cpp
//  Competition
//
//  Created by Rafael Vareto on 11/7/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#include "ColorHistogram.hpp"

ColorHistogram::ColorHistogram(
                               const int _hBin,
                               const int _sBin,
                               const cv::Size &_block,
                               const cv::Size &_stride
                               )
: hBin(_hBin), sBin(_sBin), block(_block), stride(_stride) {
    
}

ColorHistogram::~ColorHistogram() {
    
}

pair<int,int> ColorHistogram::getBlockSize() {
    return pair<int,int>(this->block.width, this->block.height);
}

Matrix ColorHistogram::run(const Image &_image) const {
    Matrix features;
    cv::Mat hsv;
    cv::cvtColor(_image, hsv, CV_BGR2HSV);
    
    int channels[] = { 0, 1 };
    
    int histSize[] = { this->hBin, this->sBin };
    
    float hranges[] = { 0, 180 };
    float sranges[] = { 0, 256 };
    const float* ranges[] = { hranges, sranges };
    
    SlideWindow::slideWindow(cv::Size(hsv.cols, hsv.rows), block, stride,
           [&](const cv::Rect & window) {
               
               cv::Mat hist, fhist;
               cv::Mat crop = hsv(window);
               
               cv::calcHist(&crop, 1, channels, cv::Mat(),
                            hist, 2, histSize, ranges, true, false);
               hist.convertTo(fhist, CV_32F);
               
               fhist = fhist.reshape(1, 1);
               features.cbind(fhist);
           });
    
    return features;
}