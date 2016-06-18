//
//  LocalBinaryPattern.hpp
//  Competition
//
//  Created by Rafael Vareto on 11/7/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#ifndef LocalBinaryPattern_hpp
#define LocalBinaryPattern_hpp

#include "Descriptor.hpp"

class LocalBinaryPattern : public Descriptor {
public:
    LocalBinaryPattern(
                       const cv::Size &_block = cv::Size(16, 16),
                       const cv::Size &_stride = cv::Size(8, 8)
                       );
    ~LocalBinaryPattern();
    
    pair<int,int> getBlockSize();
    Matrix run(const Image &_image) const;
    
private:
    const cv::Size block;
    const cv::Size stride;
};

#endif /* LocalBinaryPattern_hpp */
