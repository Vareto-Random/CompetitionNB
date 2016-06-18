//
//  HistogramOrientedGradient.hpp
//  Competition
//
//  Created by Rafael Vareto on 11/7/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#ifndef HistogramOrientedGradient_hpp
#define HistogramOrientedGradient_hpp

#include "Descriptor.hpp"

class HistogramOrientedGradient : public Descriptor {
public:
    HistogramOrientedGradient(const cv::Size &_block = cv::Size(16, 16),
                              const cv::Size &_stride = cv::Size(8, 8),
                              const cv::Size &_cell = cv::Size(8, 8)
                              );
    ~HistogramOrientedGradient();
    
    pair<int,int> getBlockSize();
    Matrix run(const Image &_image) const;
    
private:
    const cv::Size block;
    const cv::Size cell;
    const cv::Size stride;
};

#endif /* HistogramOrientedGradient_hpp */
