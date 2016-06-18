//
//  Regression.hpp
//  Competition
//
//  Created by Rafael Vareto on 11/6/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#ifndef Regression_hpp
#define Regression_hpp

#include "Matrix.hpp"

using namespace std;

class Regression {
    virtual void load(ifstream &_input) = 0;
    virtual void predict(Matrix &_samples, Matrix &resp) const = 0;
    virtual void save(ofstream &_output) = 0;
    virtual void train(Matrix &_samples, Matrix &_response) = 0;
};

#endif /* Regression_hpp */
