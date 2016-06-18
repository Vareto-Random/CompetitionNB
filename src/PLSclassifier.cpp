//
//  PLSclassifier.cpp
//  Competition
//
//  Created by Rafael Vareto on 11/7/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#include "PLSclassifier.hpp"

const std::string PLSclassifier::positiveLabel = "pos";
const std::string PLSclassifier::negativeLabel = "neg";

PLSclassifier::PLSclassifier(const int _factor) : factor(_factor){
    
}

void PLSclassifier::load(ifstream &_input) {
    _input.read((char*) &(this->factor), sizeof(this->factor));
    
    this->labels.load(_input);
    load_list_sl(_input, this->zeroMean);
    load_list_sl(_input, this->models);
}

void PLSclassifier::respond(Matrix &_samples, Matrix &_response) const {
    if(_response.rows != _samples.rows || _response.cols != models.size()) {
        _response.create(_samples.rows, models.size());
    }
    
//#pragma omp parallel for
    for (int m = 0; m < models.size(); ++m) {
        Matrix r;
        this->models[m].predict(_samples, r);
        this->zeroMean[m].unnorm(r);
        r.copyTo(_response.col(m));
    }
}

void PLSclassifier::save(ofstream &_output) {
    _output.write((char*) &(this->factor), sizeof(this->factor));

    this->labels.save(_output);
    save_list_sl(_output, this->zeroMean);
    save_list_sl(_output, this->models);
}

void PLSclassifier::train(Matrix &_samples, Labels &_labels) {
    this->labels.clear();
    
    set<string> group;
    for (const Label &label : _labels) {
        if (!label.getExtra()) {
            group.insert(label.getId());
        }
    }
    
    if (group.size() > 2) {
        for (const string &id : group) {
            this->labels.push_back(id);
        }
    } else {
        assert(group.find(PLSclassifier::positiveLabel) != group.end());
        this->labels.push_back(PLSclassifier::positiveLabel);
    }
    
    //int count = 0;
    this->models.resize(this->labels.size());
    this->zeroMean.resize(this->models.size());
    
//#pragma omp parallel for
    for (int m = 0; m < this->models.size(); ++m) {
        
//#pragma omp critical
//        {
//            cout << "id: " << ++count << '/' << this->models.size() << endl;
//        }
        
        Matrix r(_samples.rows, 1);
        r = -1.0f;
        for (int row = 0; row < r.rows; ++row)
            if(_labels[row].getId() == this->labels[m].getId()) {
                r(row) = 1.0f;
            }
        assert((*max_element(r.begin(), r.end())) != -1.0f);
        this->zeroMean[m].train(r);
        
        Matrix s = _samples.clone();
        this->models[m] = PLSregression(this->factor);
        this->models[m].train(s, r);
        //models[m].regression = samples.row(0);
    }
}