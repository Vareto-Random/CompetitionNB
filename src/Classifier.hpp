//
//  Classifier.hpp
//  Competition
//
//  Created by Rafael Vareto on 11/7/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#ifndef Classifier_hpp
#define Classifier_hpp

#include "Label.hpp"
#include "Regression.hpp"

class Classifier {
public:
    virtual void load(ifstream &_input) = 0;
    virtual void respond(Matrix &_samples, Matrix &_response) const = 0;
    virtual void save(ofstream &_output) const = 0;
    virtual void train(Matrix &_samples, Labels &_labels) = 0;
};

#endif /* Classifier_hpp */
