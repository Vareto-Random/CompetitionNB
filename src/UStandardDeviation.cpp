//
//  uStandardDeviation.cpp
//  Competition
//
//  Created by Rafael Vareto on 11/12/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#include <fstream>

#include "UStandardDeviation.hpp"

UStandardDeviation::UStandardDeviation () {
    
}

void UStandardDeviation::load(ifstream &_input) {
    this->standard.load(_input);
}

void UStandardDeviation::norm(Matrix &_matrix) const {
    assert(_matrix.cols == this->standard.cols);
    
    for(int row = 0; row < _matrix.rows; ++row) {
        MType *p = _matrix.ptr<MType>(row, 0);
        MType *c = (MType*) standard.data;
        for(int col = 0; col < _matrix.cols; ++col, ++p, ++c)
            if (*c > 1e-6)
                *p /= *c;
    }
}

void UStandardDeviation::save(ofstream &_output) const {
    this->standard.save(_output);
}

void UStandardDeviation::train(const Matrix &_matrix) {
    ZeroMean zmean;
    zmean.train(_matrix);
    
    standard.create(1, _matrix.cols);
    for (int col = 0; col < _matrix.cols; ++col) {
        
        Matrix c = _matrix.col(col).clone() - zmean.mean(col);
        c = c.t() * c / c.rows;
        
        standard(0, col) = sqrt(c());
    }
}

void UStandardDeviation::trainNorm(Matrix &_matrix) {
    this->train(_matrix);
    this->norm(_matrix);
}

void UStandardDeviation::unnorm(Matrix &_matrix) const {
    assert(_matrix.cols == standard.cols);
    
    for(int row = 0; row < _matrix.rows; ++row) {
        MType *p = _matrix.ptr<MType>(row, 0);
        MType *c = (MType*) standard.data;
        for(int col = 0; col < _matrix.cols; ++col, ++p, ++c)
            if (*c > 1e-6)
                *p *= *c;
    }
}