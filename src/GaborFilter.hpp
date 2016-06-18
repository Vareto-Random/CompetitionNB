//
//  GaborFilter.hpp
//  Competition
//
//  Created by Rafael Vareto on 11/7/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#ifndef GaborFilter_hpp
#define GaborFilter_hpp

#include "Descriptor.hpp"

class GaborFilter : public Descriptor {
public:
    GaborFilter(
                const int _scale = 5,
                const int _orientation = 8,
                const float _downscale = .25,
                const cv::Size &_kernel = cv::Size(16, 16)
                );
    ~GaborFilter();
    
    pair<int,int> getBlockSize();
    Matrix run(const Image &_image) const;
    
private:
    const int scale;
    const int orientation;
    const float downscale;
    const cv::Size kernel;
};

#endif /* GaborFilter_hpp */
