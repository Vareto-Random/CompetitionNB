//
//  ZeroScore.cpp
//  Competition
//
//  Created by Rafael Vareto on 11/12/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#include "ZeroScore.hpp"

ZeroScore::ZeroScore () {
    
}

void ZeroScore::load(ifstream &_input) {
    this->mean.load(_input);
    this->standard.load(_input);
}

void ZeroScore::norm(Matrix &_matrix) const {
    this->mean.norm(_matrix);
    this->standard.norm(_matrix);
}

void ZeroScore::save(ofstream &_output) const {
    this->mean.save(_output);
    this->standard.save(_output);
}

void ZeroScore::train(const Matrix &_matrix) {
    this->mean.train(_matrix);
    this->standard.train(_matrix);
}

void ZeroScore::trainNorm(Matrix &_matrix) {
    this->mean.trainNorm(_matrix);
    this->standard.trainNorm(_matrix);
}

void ZeroScore::unnorm(Matrix &_matrix) const {
    this->standard.unnorm(_matrix);
    this->mean.unnorm(_matrix);
}