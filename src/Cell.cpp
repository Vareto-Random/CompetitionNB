//
//  Cell.cpp
//  Competition
//
//  Created by Rafael Vareto on 11/6/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#include "Cell.hpp"

#define SIZE 16

Cell::Cell(int _x, int _y, cv::Size _imageSize) {
    this->setX(_x);
    this->setY(_y);
    this->setImageSize(_imageSize);
    this->setBlockWidth(SIZE);
    this->setBlockHeight(SIZE);
}

Cell::Cell(int _x, int _y, cv::Size _imageSize, int _blockSize) {
    this->setX(_x);
    this->setY(_y);
    this->setImageSize(_imageSize);
    this->setBlockWidth(_blockSize);
    this->setBlockHeight(_blockSize);
}

Cell::Cell(int _x, int _y, cv::Size _imageSize, int _blockWidth, int _blockHeight) {
    this->setX(_x);
    this->setY(_y);
    this->setImageSize(_imageSize);
    this->setBlockWidth(_blockWidth);
    this->setBlockHeight(_blockHeight);
}

int Cell::getX() {
    return this->x;
}

int Cell::getY() {
    return this->y;
}

int Cell::getX0() {
    return this->x0;
}

int Cell::getY0() {
    return this->y0;
}

int Cell::getBlockHeight() {
    return this->blockHeight;
}

int Cell::getBlockWidth() {
    return this->blockWidth;
}

cv::Size Cell::getImageSize() {
    return this->imageSize;
}

vector<Matrix> Cell::getFeatures() {
    return this->features;
}

bool Cell::setX(int _x) {
    bool status = true;
    if(_x < 0) {
        _x = 0;
        status = false;
    }
    this->x = _x;
    return status;
}

bool Cell::setY(int _y) {
    bool status = true;
    if(_y < 0) {
        _y = 0;
        status = false;
    }
    this->y = _y;
    return status;
}

int Cell::setX0() {
    return this->setX0(this->x);
}

int Cell::setX0(int _x) {
    int tempX0 = std::abs(_x - (int) this->blockWidth / 2);
    int tempXN = std::abs(_x + (int) this->blockWidth / 2);
    
    if (tempX0 < 0) {
        this->x0 = 0;
    } else if (tempXN > this->imageSize.width) {
        this->x0 = this->imageSize.width - this->blockWidth;
    } else {
        this->x0 = tempX0;
    }
    return this->x0;
}

int Cell::setY0() {
    return this->setY0(this->y);
}

int Cell::setY0(int _y) {
    int tempY0 = std::abs(_y - (int) this->blockHeight / 2);
    int tempYN = std::abs(_y + (int) this->blockHeight / 2);
    
    if (tempY0 < 0) {
        this->y0 = 0;
    } else if (tempYN > this->imageSize.height) {
        this->y0 = this->imageSize.height - this->blockHeight;
    } else {
        this->y0 = tempY0;
    }
    return this->y0;
}

bool Cell::setBlockHeight(int _blockHeight) {
    bool status = true;
    if(_blockHeight <= 0) {
        _blockHeight = SIZE;
        status = false;
    }
    this->blockHeight = _blockHeight;
    this->setY0();
    return status;
}

bool Cell::setBlockWidth(int _blockWidth) {
    bool status = true;
    if(_blockWidth <= 0) {
        _blockWidth = SIZE;
        status = false;
    }
    this->blockWidth = _blockWidth;
    this->setX0();
    return status;
}

bool Cell::setImageSize(cv::Size _imageSize) {
    this->imageSize = _imageSize;
    return true;
}

void Cell::setFeature(cv::Mat &_image, Descriptor &_descriptor) {
    this->features.push_back(_descriptor.run(_image));
}