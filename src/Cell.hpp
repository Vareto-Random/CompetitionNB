//
//  Cell.hpp
//  Competition
//
//  Created by Rafael Vareto on 11/6/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#ifndef Cell_hpp
#define Cell_hpp

#include <vector>

#include "Descriptor.hpp"
#include "Matrix.hpp"

using namespace std;

class Cell {
public:
    Cell(int _x, int _y, cv::Size _imageSize);
    Cell(int _x, int _y, cv::Size _imageSize, int _blockSize);
    Cell(int _x, int _y, cv::Size _imageSize, int _blockWidth, int _blockHeight);
    
    int getX();
    int getY();
    int getX0();
    int getY0();
    
    int getBlockHeight();
    int getBlockWidth();
    cv::Size getImageSize();
    
    vector<Matrix> getFeatures();

    bool setX(int _x);
    bool setY(int _y);
    int setX0();
    int setX0(int _x);
    int setY0();
    int setY0(int _y);
    
    bool setBlockHeight(int _height);
    bool setBlockWidth(int _width);
    bool setImageSize(cv::Size _imageSize);
    
    void setFeature(cv::Mat &_image, Descriptor &_descriptor);
    
private:
    int x;
    int y;
    int x0;
    int y0;
    
    int blockWidth;
    int blockHeight;

    cv::Size imageSize;
    vector<Matrix> features;
};

#endif /* Cell_hpp */
