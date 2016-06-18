//
//  Descriptor.hpp
//  Competition
//
//  Created by Rafael Vareto on 11/7/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#ifndef Descriptor_hpp
#define Descriptor_hpp

#include "Matrix.hpp"
#include "SlideWindow.hpp"
#include "Useful.hpp"

class Descriptor {
public:
    virtual pair<int,int> getBlockSize() = 0;
    virtual Matrix run(const Image &_image) const = 0;
};

#endif /* Descriptor_hpp */
