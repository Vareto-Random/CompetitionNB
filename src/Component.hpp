//
//  Component.hpp
//  Competition
//
//  Created by Rafael Vareto on 11/15/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#ifndef Component_hpp
#define Component_hpp

#include <vector>

#include "Descriptor.hpp"
#include "Matrix.hpp"

using namespace std;

class Component {
public:
    Component();
    Component(int _x, int _y, int _width, int _height);
    Component(int _x, int _y, int _width, int _height, cv::Mat &_image, Descriptor &_descriptor);
    
    int getX();
    int getY();
    
    int getBlockHeight();
    int getBlockWidth();
    
    string getName();
    
    vector<Matrix> getFeatures();
    
    bool setX(int _x);
    bool setY(int _y);
    
    bool setBlockHeight(int _height);
    bool setBlockWidth(int _width);
    
    bool setName(string _name);
    void setFeature(cv::Mat &_image, Descriptor &_descriptor);
    
private:
    int x;
    int y;
    
    int blockWidth;
    int blockHeight;
    
    string name;
    vector<Matrix> features;
};


#endif /* Component_hpp */
