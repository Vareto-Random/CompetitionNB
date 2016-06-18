//
//  Norm.hpp
//  Competition
//
//  Created by Rafael Vareto on 11/7/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#ifndef Norm_hpp
#define Norm_hpp

#include <fstream>

#include <opencv2/features2d/features2d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/ml/ml.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/opencv.hpp>

#include "Matrix.hpp"

class Norm {
public:
    virtual void load(ifstream &_input) = 0;
    virtual void norm(Matrix &_matrix) const = 0;
    virtual void unnorm(Matrix &_matrix) const = 0;
    virtual void save(ofstream &_output) const = 0;
    virtual void train(const Matrix &_matrix) = 0;
    virtual void trainNorm(Matrix &_matrix) = 0;
};

#endif /* Norm_hpp */
