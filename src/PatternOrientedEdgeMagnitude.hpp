//
//  PatternOrientedEdgeMagnitude.hpp
//  Competition
//
//  Created by Rafael Vareto on 11/7/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#ifndef PatternOrientedEdgeMagnitude_hpp
#define PatternOrientedEdgeMagnitude_hpp

#include "Descriptor.hpp"
#include "CompoundLocalBinaryPattern.hpp"

typedef float MType;

class PatternOrientedEdgeMagnitude : public Descriptor {
public:
    PatternOrientedEdgeMagnitude(
                                 const int _bins = 3,
                                 const int _radius = 5,
                                 const cv::Size &_cell = cv::Size(7, 7),
                                 const cv::Size &_block = cv::Size(16, 16),
                                 const cv::Size &_stride = cv::Size(8, 8)
                                 );
    ~PatternOrientedEdgeMagnitude();
    
    pair<int,int> getBlockSize();
    Matrix run(const Image &_image) const;
    
private:
    const int bins;
    const cv::Size cell;
    CompoundLocalBinaryPattern clbp;
};

#endif /* PatternOrientedEdgeMagnitude_hpp */
