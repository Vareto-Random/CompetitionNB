//
//  Matrix.hpp
//  Competition
//
//  Created by Rafael Vareto on 11/6/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#ifndef Matrix_hpp
#define Matrix_hpp

#include <iostream>
#include <fstream>
#include <vector>

#include <opencv2/highgui/highgui.hpp>

using namespace std;

typedef float MType;

class Matrix : public cv::Mat_<MType> {
public:
    Matrix();
    Matrix(const int _rows, const int _cols);
    Matrix(cv::MatExpr mat);
    Matrix(cv::Mat_<MType> _matrix);
    Matrix(cv::Mat mat);
    
    Matrix& operator=(const float _value);
    
    float& operator()();
    float& operator()(const int _index);
    float& operator()(const int _rows, const int _cols);
    
    const float& operator()() const;
    const float& operator()(const int _index) const;
    const float& operator()(const int _rows, const int _cols) const;
    
    void cbind(const Matrix &_matrix);
    void rbind(const Matrix &_matrix);
    void shuffle();
    void save(ofstream &_output) const;
    void load(ifstream &_input);
};

#endif /* Matrix_hpp */
