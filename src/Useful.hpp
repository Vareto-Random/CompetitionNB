//
//  Useful.hpp
//  Competition
//
//  Created by Rafael Vareto on 11/7/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#ifndef Useful_hpp
#define Useful_hpp

#include <opencv2/opencv.hpp>

#include "Label.hpp"
#include "Matrix.hpp"
#include "PLSclassifier.hpp"
#include "PLSregression.hpp"

typedef cv::Mat Image;

class Useful {
public:
    static void gradient(const Image &_image, Matrix &_orientation, Matrix &_magnitude);
    static void save2file(const PLSclassifier &_model, const Matrix &_responses, const Labels &_probeLabels);
};

#endif /* Useful_hpp */
