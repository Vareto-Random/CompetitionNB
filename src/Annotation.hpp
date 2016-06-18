//
//  Annotations.hpp
//  Competition
//
//  Created by Rafael Vareto on 10/22/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//


#ifndef Annotations_hpp
#define Annotations_hpp

#include <iostream>

using namespace std;

class Annotation {
public:
    Annotation();
    Annotation(string _file, int _posX, int _posY, int _width, int _height);
    virtual ~Annotation();
    
    void toString();
    
public:
    string file;
    int posX;
    int posY;
    int width;
    int height;

};

#endif /* Annotations_hpp */
