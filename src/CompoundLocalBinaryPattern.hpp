//
//  CompoundLocalBinaryPattern.hpp
//  Competition
//
//  Created by Rafael Vareto on 11/7/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#ifndef CompoundLocalBinaryPattern_hpp
#define CompoundLocalBinaryPattern_hpp

#include <unordered_map>

#include "Descriptor.hpp"

class CompoundLocalBinaryPattern : public Descriptor {
public:
    CompoundLocalBinaryPattern(
                               const int _radius = 5,
                               const cv::Size &_block = cv::Size(16, 16),
                               const cv::Size &_stride = cv::Size(8, 8)
                               );
    ~CompoundLocalBinaryPattern();
    
    pair<int,int> getBlockSize();
    Matrix run(const Image &_image) const;
    
    template<typename Type>
    Matrix& structure(const cv::Mat &_matrix, Matrix &_descriptor, float _tau = 3, const int _maxTransitions = 2) const;

private:
    const int radius;
    const cv::Size block;
    const cv::Size stride;
};


template<typename Type>
Matrix& CompoundLocalBinaryPattern::structure(const cv::Mat &_matrix, Matrix &_descriptor, float _tau, const int _maxTransitions) const {
    // compute code map
    unordered_map<uchar, uchar> codemap;
    uchar codeid = 1;
    for (int code = 0; code < 256; ++code) {
        
        // set bits to each transition
        char b = ((char) code) >> 1;
        char c = code ^ b;
        // count number of bits in c
        c = c - ((c >> 1) & 0x55555555);
        c = (c & 0x33333333) + ((c >> 2) & 0x33333333);
        int t = (((c + (c >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
        
        if (t > _maxTransitions)
            codemap[code] = 0;
        else
            codemap[code] = codeid++;
    }
    
    _descriptor.release();
    
    Image lbp_image(_matrix.rows - 2 * this->radius, _matrix.cols - 2 * this->radius, CV_8UC1);
    
    // iterate through your data
    for (int i = this->radius; i < _matrix.rows - this->radius; i++) {
        for (int j = this->radius; j < _matrix.cols - this->radius; j++) {
            char code = 0;
            for (int n = 0; n < 8; n++) {
                
                // sample points
                float x = this->radius * cos(2.0 * M_PI * n / (float) 8);
                float y = this->radius * -sin(2.0 * M_PI * n / (float) 8);
                
                // relative indices
                int fx = floor(x);
                int fy = floor(y);
                int cx = ceil(x);
                int cy = ceil(y);
                
                // fractional part
                float ty = y - fy;
                float tx = x - fx;
                
                // set interpolation weights
                float w1 = (1 - tx) * (1 - ty);
                float w2 = tx * (1 - ty);
                float w3 = (1 - tx) * ty;
                float w4 = tx * ty;
                
                float t = w1 * _matrix.at<Type>(i + fy, j + fx)
                + w2 * _matrix.at<Type>(i + fy, j + cx)
                + w3 * _matrix.at<Type>(i + cy, j + fx)
                + w4 * _matrix.at<Type>(i + cy, j + cx);
                
                bool bit = ((t > _matrix.at<Type>(i, j)) and (std::abs(t - _matrix.at<Type>(i, j)) > _tau));
                
                code += bit << n;
            }
            lbp_image.at<uchar>(i - radius, j - radius) = codemap[code];
        }
    }
    
    const int channels[] = { 0 };
    const int histSize[] = { static_cast<int>(codeid) };
    const float range[] = { 0, static_cast<float>(codeid) };
    const float* ranges[] = { range };
    
    cv::Size _block = block;
    if(_block.width > lbp_image.cols)
        _block.width = lbp_image.cols;
    if(_block.height > lbp_image.rows)
        _block.height = lbp_image.rows;
        
    SlideWindow::slideWindow(lbp_image, _block, stride, [&](Image & crop) {
        cv::Mat hist;
        
        cv::calcHist(&crop, 1, channels, cv::Mat(), hist, 1, histSize, ranges, true, false);
        hist.convertTo(hist, CV_32F);
        hist = hist.reshape(1, 1);
        hist /= cv::sum(hist)[0];
        _descriptor.cbind(hist);
    });
    
    return _descriptor;
}

#endif /* CompoundLocalBinaryPattern_hpp */
