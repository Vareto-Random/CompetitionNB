//
//  uStandardDeviation.hpp
//  Competition
//
//  Created by Rafael Vareto on 11/12/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#ifndef uStandardDeviation_hpp
#define uStandardDeviation_hpp

#include "Norm.hpp"
#include "ZeroMean.hpp"

class UStandardDeviation : public Norm {
public:
    UStandardDeviation();
    void load(ifstream &_input);
    void norm(Matrix &_matrix) const;
    void save(ofstream &_output) const;
    void train(const Matrix &_matrix);
    void trainNorm(Matrix &_matrix);
    void unnorm(Matrix &_matrix) const;

    Matrix standard;
};

#endif /* uStandardDeviation_hpp */
