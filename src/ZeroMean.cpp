//
//  zeroMean.cpp
//  Competition
//
//  Created by Rafael Vareto on 11/7/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#include "ZeroMean.hpp"

ZeroMean::ZeroMean () {
    
}

void ZeroMean::load(ifstream &_input) {
    this->mean.load(_input);
}

void ZeroMean::norm(Matrix &_matrix) const {
    assert(_matrix.cols == this->mean.cols);
    
    for(int row = 0; row < _matrix.rows; ++row) {
        MType *p = _matrix.ptr<MType>(row, 0);
        MType *c = (MType*) this->mean.data;
        for(int col = 0; col < _matrix.cols; ++col, ++p, ++c) {
            *p -= *c;
        }
    }
}

void ZeroMean::save(ofstream &_output) const {
    this->mean.save(_output);
}

void ZeroMean::train(const Matrix &_matrix) {
    cv::reduce(_matrix, mean, 0, CV_REDUCE_AVG);
}

void ZeroMean::trainNorm(Matrix &_matrix) {
    this->train(_matrix);
    this->norm(_matrix);
}

void ZeroMean::unnorm(Matrix &_matrix) const {
    assert(_matrix.cols == this->mean.cols);
    
    for(int row = 0; row < _matrix.rows; ++row) {
        MType *p = _matrix.ptr<MType>(row, 0);
        MType *c = (MType*) this->mean.data;
        for(int col = 0; col < _matrix.cols; ++col, ++p, ++c) {
            *p += *c;
        }
    }
}