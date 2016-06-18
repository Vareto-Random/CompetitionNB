//
//  Component.cpp
//  Competition
//
//  Created by Rafael Vareto on 11/15/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#include "Component.hpp"

#define SIZE 16

Component::Component() {
    this->x = 0;
    this->y = 0;
    this->blockWidth = 0;
    this->blockHeight = 0;
}

Component::Component(int _x, int _y, int _width, int _height) {
    this->setX(_x);
    this->setY(_y);
    this->setBlockWidth(_width);
    this->setBlockHeight(_height);
}

Component::Component(int _x, int _y, int _width, int _height, cv::Mat &_image, Descriptor &_descriptor) {
    this->setX(_x);
    this->setY(_y);
    this->setBlockWidth(_width);
    this->setBlockHeight(_height);
    this->setFeature(_image, _descriptor);
}

int Component::getX() {
    return this->x;
}

int Component::getY() {
    return this->y;
}

int Component::getBlockWidth() {
    return this->blockWidth;
}

int Component::getBlockHeight() {
    return this->blockHeight;
}

string Component::getName() {
    return this->name;
}

vector<Matrix> Component::getFeatures() {
    return this->features;
}

bool Component::setX(int _x) {
    bool status = true;
    if(_x < 0) {
        _x = 0;
        status = false;
    }
    this->x = _x;
    return status;
}

bool Component::setY(int _y) {
    bool status = true;
    if(_y < 0) {
        _y = 0;
        status = false;
    }
    this->y = _y;
    return status;
}

bool Component::setBlockWidth(int _width) {
    bool status = true;
    if(_width <= 0) {
        _width = SIZE;
        status = false;
    }
    this->blockWidth = _width;
    return status;
}

bool Component::setBlockHeight(int _height) {
    bool status = true;
    if(_height <= 0) {
        _height = SIZE;
        status = false;
    }
    this->blockHeight = _height;
    return status;
}

bool Component::setName(string _name) {
    this->name = _name;
    return true;
}

void Component::setFeature(cv::Mat &_image, Descriptor &_descriptor) {
    this->features.push_back(_descriptor.run(_image));
}