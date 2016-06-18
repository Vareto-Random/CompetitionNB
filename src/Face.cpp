//
//  Face.cpp
//  Competition
//
//  Created by Rafael Vareto on 12/10/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#include "Face.hpp"

Face::Face() {
    
}

Face::Face(cv::Mat &_image, Descriptor &_descriptor) {
    this->setFeature(_image, _descriptor);
}

void Face::clear() {
    this->name.clear();
    this->features.clear();
}

string Face::getName() {
    return this->name;
}

vector<Matrix> Face::getFeatures() {
    return this->features;
}

bool Face::setName(string _name) {
    this->name = _name;
    return true;
}

void Face::setFeature(cv::Mat &_image, Descriptor &_descriptor) {
    this->features.push_back(_descriptor.run(_image));
}