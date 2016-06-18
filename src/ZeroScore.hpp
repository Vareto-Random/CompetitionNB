//
//  ZeroScore.hpp
//  Competition
//
//  Created by Rafael Vareto on 11/12/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#ifndef ZeroScore_hpp
#define ZeroScore_hpp

#include "Norm.hpp"
#include "UStandardDeviation.hpp"
#include "ZeroMean.hpp"

class ZeroScore : public Norm {
public:
    ZeroScore();
    void load(ifstream &_input);
    void norm(Matrix &_matrix) const;
    void save(ofstream &_output) const;
    void train(const Matrix &_matrix);
    void trainNorm(Matrix &_matrix);
    void unnorm(Matrix &_matrix) const;

    UStandardDeviation standard;
    ZeroMean mean;
};

#endif /* ZeroScore_hpp */
