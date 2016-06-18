//
//  PLSregression.hpp
//  Competition
//
//  Created by Rafael Vareto on 11/7/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#ifndef PLSregression_hpp
#define PLSregression_hpp

#include <stdio.h>

#include "Regression.hpp"

class PLSregression : public Regression {
public:
    PLSregression(const int _factor = 3);
    
    void load(ifstream &_input);
    void predict(Matrix &_samples, Matrix &_response) const;
    void save(ofstream &_output) ;
    void train(Matrix &_samples, Matrix &_response);
    
    void nipals(Matrix _X, Matrix _Y, Matrix &_T, Matrix &_P, Matrix &_U, Matrix &_Q, Matrix &_W, Matrix &_B);
    
public:
    int factor;
    Matrix regression;
};

#endif /* PLSregression_hpp */
