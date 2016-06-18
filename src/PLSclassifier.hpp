//
//  PLSclassifier.hpp
//  Competition
//
//  Created by Rafael Vareto on 11/7/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#ifndef PLSclassifier_hpp
#define PLSclassifier_hpp

#include <fstream>
#include <set>

#include "Classifier.hpp"
#include "Label.hpp"
#include "PLSregression.hpp"
#include "Template.hpp"
#include "ZeroMean.hpp"

using namespace std;

class PLSclassifier {
public:
    PLSclassifier(const int _factor = 3);
    
    void load(ifstream &_input);
    void respond(Matrix &_samples, Matrix &_response) const;
    void save(ofstream &_output);
    void train(Matrix &_samples, Labels &_labels);
    
//    template<typename T>
//    static void load_list_sl(std::ifstream &input, std::vector<T> &list);
//    template<typename T>
//    static void save_list_rw(std::ofstream &output, const std::vector<T> &list);
    
    static const string negativeLabel;
    static const string positiveLabel;
    
//private:
    int factor;
    Labels labels;
    vector<PLSregression> models;
    vector<ZeroMean> zeroMean;
};


#endif /* PLSclassifier_hpp */
