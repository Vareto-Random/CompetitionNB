//
//  MeanIntensity.hpp
//  Competition
//
//  Created by Rafael Vareto on 11/7/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#ifndef MeanIntensity_hpp
#define MeanIntensity_hpp

#include "Descriptor.hpp"

class MeanIntensity : public Descriptor {
public:
    MeanIntensity(
                  const cv::Size &_block = cv::Size(4, 4),
                  const cv::Size &_stride = cv::Size(2, 2)
                  );
    ~MeanIntensity();
    
    pair<int,int> getBlockSize();
    Matrix run(const Image &_image) const;
    
private:
    const cv::Size block;
    const cv::Size stride;
};

#endif /* MeanIntensity_hpp */
