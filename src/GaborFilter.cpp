//
//  GaborFilter.cpp
//  Competition
//
//  Created by Rafael Vareto on 11/7/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#include "GaborFilter.hpp"

GaborFilter::GaborFilter(
                         const int _scale,
                         const int _orientation,
                         const float _downscale,
                         const cv::Size &_kernel)
: scale(_scale), orientation(_orientation), downscale(_downscale), kernel(_kernel) {
    
}

GaborFilter::~GaborFilter() {
    
}

pair<int,int> GaborFilter::getBlockSize() {
    return pair<int,int>(this->kernel.width, this->kernel.height);
}

Matrix GaborFilter::run(const Image &_image) const {
    Image gray;
    Matrix features;
    
    // Gabor Filter
    cv::cvtColor(_image, gray, CV_RGB2GRAY);
    
    // test for 5 scales
    for (int u = 0; u < this->scale; ++u) {
        
        float f = 1.414213562;
        float k = M_PI_2 / pow(f, u);
        
        // test for 8 orientations
        for (int v = 0; v < this->orientation; ++v) {
            
            float phi = v * M_PI / this->orientation;
            
            // build kernel
            Image rk(kernel.width * 2 + 1, this->kernel.height * 2 + 1, CV_32F); // real part
            Image ik(kernel.width * 2 + 1, this->kernel.height * 2 + 1, CV_32F); // imaginary part
            for (int x = -this->kernel.width; x <= this->kernel.width; ++x) {
                for (int y = -this->kernel.height; y <= this->kernel.height; ++y) {
                    float _x = x * cos(phi) + y * sin(phi);
                    float _y = -x * sin(phi) + y * cos(phi);
                    float c = exp(-(_x * _x + _y * _y) / (4 * M_PI * M_PI));
                    rk.at<float>(x + this->kernel.width, y + this->kernel.height) = c * cos(k * _x);
                    ik.at<float>(x + this->kernel.width, y + this->kernel.height) = c * sin(k * _x);
                }
            }
            
            // convolve with image
            Image i, r;
            cv::filter2D(gray, r, CV_32F, rk);
            cv::filter2D(gray, i, CV_32F, ik);
            
            // calc mag
            Image mag;
            cv::pow(i, 2, i);
            cv::pow(r, 2, r);
            cv::pow(i + r, 0.5, mag);
            
            // downsampling
            cv::resize(mag, mag, cv::Size(), this->downscale, this->downscale, CV_INTER_NN);
            
            // store
            features.rbind(mag);
        }
    }
    return features;
}