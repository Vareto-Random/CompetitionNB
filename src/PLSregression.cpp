//
//  PLSregression.cpp
//  Competition
//
//  Created by Rafael Vareto on 11/7/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#include "PLSregression.hpp"

PLSregression::PLSregression(const int _factor) {
    //cout << _factor;
    this->factor = _factor;
}

void PLSregression::load(ifstream &_input) {
    _input.read((char*) &(this->factor), sizeof (this->factor));
    this->regression.load(_input);
}

void PLSregression::predict(Matrix &_samples, Matrix &_response) const {
    assert(_samples.cols == this->regression.cols);
    
    if (_response.cols != this->regression.rows || _response.rows != _samples.rows) {
        _response.create(_samples.rows, this->regression.rows);
    }
    
    for (int row = 0; row < _samples.rows; ++row) {
        for (int reg = 0; reg < this->regression.rows; ++reg) {
            
            const MType *s = _samples.ptr<MType>(row, 0);
            const MType *r = this->regression.ptr<MType>(reg, 0);
            MType *t = _response.ptr<MType>(row, reg);
            *t = 0;
            
            for (int col = 0; col < _samples.cols; ++col, ++s, ++r) {
                *t += (*s) * (*r);
            }
        }
    }
}

void PLSregression::save(ofstream &_output) {
    _output.write((char*) &(this->factor), sizeof (this->factor));
    this->regression.save(_output);
}

void PLSregression::train(Matrix &_samples, Matrix &_response) {
    Matrix T, P, U, Q, W, B;
    
    this->nipals(_samples, _response.clone(), T, P, U, Q, W, B);
    this->regression = ((W * (P.t() * W).inv(cv::DECOMP_SVD)) * (T.t() * T).inv(cv::DECOMP_SVD) * T.t() * _response).t();
}

void PLSregression::nipals(Matrix _X, Matrix _Y, Matrix &_T, Matrix &_P, Matrix &_U, Matrix &_Q, Matrix &_W, Matrix &_B) {
    //Setting the termination criteria
    int MaxIndexX, MaxIndexY, nMaxOuter = 10;
    double MaxValX, MaxValY, TempVal, TermCrit = 10e-6;
    Matrix tNorm, TempX, TempY;
    
    //Matrices for storing the intermediate values.
    Matrix tTemp, tNew, uTemp, wTemp, qTemp, pTemp, bTemp;
    
    //Allocating memory
    _T.create(_X.rows, this->factor);
    _P.create(_X.cols, this->factor);
    _U.create(_Y.rows, this->factor);
    _Q.create(_Y.cols, this->factor);
    _W.create(_X.cols, this->factor);
    _B.create(this->factor, 1);
    tTemp.create(_X.rows, 1);
    uTemp.create(_Y.rows, 1);
    
    for (int index1 = 0; index1 < this->factor; index1++) {
        //Finding the column having the highest norm
        MaxValX = 0;
        MaxValY = 0;
        MaxIndexX = 0;
        MaxIndexY = 0;
        TempX.create(_X.rows, 1);
        TempY.create(_Y.rows, 1);
        for (int index3 = 0; index3 < _X.cols; index3++) {
            for (int index2 = 0; index2 < _X.rows; index2++) {
                TempX.at<float>(index2, 0) = _X.at<float>(index2, index3);
            }
            if (cv::norm(TempX) > MaxValX) {
                MaxValX = cv::norm(TempX);
                MaxIndexX = index3;
            }
        }
        for (int index3 = 0; index3 < _Y.cols; index3++) {
            for (int index2 = 0; index2 < _Y.rows; index2++) {
                TempY.at<float>(index2, 0) = _Y.at<float>(index2, index3);
            }
            if (cv::norm(TempY) > MaxValY) {
                MaxValY = cv::norm(TempY);
                MaxIndexY = index3;
            }
        }
        
        for (int index3 = 0; index3 < _X.rows; index3++) {
            tTemp.at<float>(index3, 0) = _X.at<float>(index3, MaxIndexX);
            uTemp.at<float>(index3, 0) = _Y.at<float>(index3, MaxIndexY);
        }
        
        // Iteration for Outer Modelling
        for (int index2 = 0; index2 < nMaxOuter; index2++) {
            wTemp = _X.t() * uTemp;
            wTemp = wTemp / cv::norm(wTemp);
            tNew = _X * wTemp;
            qTemp = _Y.t() * tNew;
            qTemp = qTemp / cv::norm(qTemp);
            uTemp = _Y * qTemp;
            
            TempVal = cv::norm(tTemp - tNew);
            if (cv::norm(tTemp - tNew) < TermCrit) {
                break;
            }
            tTemp = tNew.clone();
        }
        
        // Residual Deflation
        tNorm = tTemp.t() * tTemp;
        bTemp = uTemp.t() * tTemp / tNorm.at<float>(0, 0);
        pTemp = _X.t() * tTemp / tNorm.at<float>(0, 0);
        _X = _X - tTemp * pTemp.t();
        _Y = _Y - bTemp.at<float>(0, 0) * (tTemp * qTemp.t());
        
        
        // Saving Results to Outputs.
        for (int index3 = 0; index3 != _X.rows; index3++) {
            _T.at<float>(index3, index1) = tTemp.at<float>(index3, 0);
            _U.at<float>(index3, index1) = uTemp.at<float>(index3, 0);
        }
        for (int index3 = 0; index3 != _X.cols; index3++) {
            _P.at<float>(index3, index1) = pTemp.at<float>(index3, 0);
            _W.at<float>(index3, index1) = wTemp.at<float>(index3, 0);
        }
        
        for (int index3 = 0; index3 != qTemp.rows; index3++) {
            _Q.at<float>(index3, index1) = qTemp.at<float>(index3, 0);
        }
        _B.at<float>(index1, 0) = bTemp.at<float>(0, 0);
        
        // Checking residual
        if ((cv::norm(_X) == 0) || (cv::norm(_Y) == 0)) {
            break;
        }
    }
}