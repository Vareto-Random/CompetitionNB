//
//  zeroMean.hpp
//  Competition
//
//  Created by Rafael Vareto on 11/7/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#ifndef zeroMean_hpp
#define zeroMean_hpp

#include "Norm.hpp"

class ZeroMean : public Norm {
public:
    ZeroMean();
    void load(ifstream &_input);
    void norm(Matrix &_matrix) const;
    void save(ofstream &_output) const;
    void train(const Matrix &_matrix);
    void trainNorm(Matrix &_matrix);
    void unnorm(Matrix &_matrix) const;
    
    Matrix mean;
};

#endif /* zeroMean_hpp */
