//
//  Matrix.cpp
//  Competition
//
//  Created by Rafael Vareto on 11/6/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#include "Matrix.hpp"

Matrix::Matrix() {
    
}

Matrix::Matrix(const int rows, const int cols) : Mat_<MType>(rows, cols) {
    
}

Matrix::Matrix(cv::MatExpr mat) : Mat_<MType>(mat) {
    
}

Matrix::Matrix(cv::Mat_<MType> mat) : Mat_<MType>(mat) {
    
}

Matrix::Matrix(cv::Mat mat) : Mat_<MType>((Mat_<MType>) mat) {
    assert(mat.type() == CV_32F);
}

Matrix& Matrix::operator=(const MType _value) {
    ((cv::Mat_<MType>) * this) = _value;
    return (*this);
}

MType& Matrix::operator()() {
    assert(rows == 1 and cols == 1);
    return at<MType>(0, 0);
}

MType& Matrix::operator()(const int _index) {
    assert(rows == 1 or cols == 1);
    
    if (rows == 1)
        return at<MType>(0, _index);
    return at<MType>(_index, 0);
}

MType& Matrix::operator()(const int _rows, const int _cols) {
    return at<MType>(_rows, _cols);
}

const MType& Matrix::operator()() const {
    assert(rows == 1 && cols == 1);
    return at<MType>(0, 0);
}

const MType& Matrix::operator()(const int _index) const {
    assert(rows == 1 || cols == 1);
    
    if (rows == 1)
        return at<MType>(0, _index);
    return at<MType>(_index, 0);
}

const MType& Matrix::operator()(const int _rows, const int _cols) const {
    return at<MType>(_rows, _cols);
}

void Matrix::cbind(const Matrix &_matrix) {
    if (empty()) {
        (*this) = _matrix.clone();
    } else {
        cv::hconcat(*this, _matrix, *this);
    }
}

void Matrix::rbind(const Matrix &_matrix) {
    if (empty()) {
        (*this) = _matrix.clone();
    } else {
        cv::vconcat(*this, _matrix, *this);
    }
}

void Matrix::shuffle() {
    vector<int> indexes;
    for (int c = 0; c < rows; ++c) {
        indexes.push_back(c);
    }
    
    random_shuffle(indexes.begin(), indexes.end());
    
    Matrix output;
    for (int c = 0; c < rows; c++) {
        output.push_back(row(indexes[c]));
    }
    
    (*this) = output;
}

void Matrix::save(std::ofstream &_output) const {
    // number of columns
    _output.write((char*) &rows, sizeof (rows));
    _output.write((char*) &cols, sizeof (cols));
    // regression
    _output.write((char*) data, rows * cols * sizeof (MType));
}

void Matrix::load(std::ifstream &_input) {
    int cols, rows;
    _input.read((char*) &rows, sizeof (rows));
    _input.read((char*) &cols, sizeof (cols));
    
    // regression
    create(rows, cols);
    _input.read((char*) data, rows * cols * sizeof (MType));
}
