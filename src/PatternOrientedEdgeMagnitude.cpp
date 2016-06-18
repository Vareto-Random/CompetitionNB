//
//  PatternOrientedEdgeMagnitude.cpp
//  Competition
//
//  Created by Rafael Vareto on 11/7/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#include "PatternOrientedEdgeMagnitude.hpp"

PatternOrientedEdgeMagnitude::PatternOrientedEdgeMagnitude(const int _bins,
                                                           const int _radius,
                                                           const cv::Size &_cell,
                                                           const cv::Size &_block,
                                                           const cv::Size &_stride)
: bins(_bins), cell(_cell), clbp(_radius, _block, _stride) {
    
}

PatternOrientedEdgeMagnitude::~PatternOrientedEdgeMagnitude() {
    
}

pair<int,int> PatternOrientedEdgeMagnitude::getBlockSize() {
    return pair<int,int>(this->clbp.getBlockSize().first, this->clbp.getBlockSize().second);
}

Matrix PatternOrientedEdgeMagnitude::run(const Image &_image) const {
    Matrix descriptor;
    
    // compute gradient image
    Matrix mag, ori;
    Useful::gradient(_image, ori, mag);
    
    int horizontalSide = this->cell.width / 2;
    int verticalSide = this->cell.height / 2;
    vector<Matrix> hist(this->bins);
    for (int h = 0; h < this->bins; ++h) {
        hist[h] = Matrix::zeros(mag.rows - verticalSide * 2, mag.cols - horizontalSide * 2);
    }
    
    // compute histogram and replace mid pixel
    SlideWindow::slideWindow(mag, this->cell, cv::Size(1, 1), [&](const cv::Rect & window) {
        for (int row = 0; row < window.height; ++row) {
            for (int col = 0; col < window.width; ++col) {
                
                float o = ori(window.y + row, window.x + col);
                float m = mag(window.y + row, window.x + col);
                
                o += M_PI_2;
                int bin = o / ((M_PI + 0.001) / this->bins);
                
                hist[bin](window.x, window.y) += m;
            }
        }
    });
    
    // compute LBP structure
    for (int o = 0; o < bins; ++o) {
        Matrix output;
        descriptor.cbind(clbp.structure<MType>(hist[o], output));
    }
    
    return descriptor;
}