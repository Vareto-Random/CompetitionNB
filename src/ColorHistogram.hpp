//
//  ColorHistogram.hpp
//  Competition
//
//  Created by Rafael Vareto on 11/7/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#ifndef ColorHistogram_hpp
#define ColorHistogram_hpp

#include "Descriptor.hpp"

class ColorHistogram : public Descriptor {
public:
    ColorHistogram(
                   const int _hBin = 20,
                   const int _sBin = 32,
                   const cv::Size &_block = cv::Size(16, 16),
                   const cv::Size &_stride = cv::Size(8, 8)
                   );
    ~ColorHistogram();
    
    pair<int,int> getBlockSize();
    Matrix run(const Image &_image) const;
    
private:
    const int hBin;
    const int sBin;
    const cv::Size block;
    const cv::Size stride;
};

#endif /* ColorHistogram_hpp */
