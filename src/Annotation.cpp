//
//  Annotations.cpp
//  Competition
//
//  Created by Rafael Vareto on 10/22/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#include "Annotation.hpp"

Annotation::Annotation() {
    
}

Annotation::Annotation(string _file, int _posX, int _posY, int _width, int _height) {
    this->file = _file;
    this->posX = _posX;
    this->posY = _posY;
    this->width = _width;
    this->height = _height;
}

Annotation::~Annotation() {
    
}

void Annotation::toString() {
    cout << "X:" << this->posX << " Y:" << this->posY << " W:" << this->width << " H:" << this->height << endl;
 }

