//
//  Face.hpp
//  Competition
//
//  Created by Rafael Vareto on 12/10/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#ifndef Face_hpp
#define Face_hpp

#include <vector>

#include "Descriptor.hpp"
#include "Matrix.hpp"

class Face {
public:
    Face();
    Face(cv::Mat &_image, Descriptor &_descriptor);
    
    void clear();
    
    string getName();
    vector<Matrix> getFeatures();
    
    bool setName(string _name);
    void setFeature(cv::Mat &_image, Descriptor &_descriptor);

private:
    string name;
    vector<Matrix> features;
};

#endif /* Face_hpp */
