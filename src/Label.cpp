//
//  Label.cpp
//  Competition
//
//  Created by Rafael Vareto on 11/7/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#include "Label.hpp"

Label::Label() {
    this->extra = false;
}

Label::Label(const string &_id, const bool _extra) {
    this->extra = _extra;
    this->id = _id;
}

void Label::save(ofstream &_output) const {
    _output.write((char*) &extra, sizeof (extra));
    _output << id << '\n';
}

void Label::load(ifstream &_input) {
    _input.read((char*) &extra, sizeof (extra));
    _input >> id;
    
    char dump;
    _input.read(&dump, sizeof (dump));
}

const bool Label::getExtra() const {
    return this->extra;
}

const string Label::getId() const {
    return this->id;
}

bool Label::setExtra(const bool _extra) {
    this->extra = _extra;
    return this->extra;
}

bool Label::setId(const string _id) {
    this->id = _id;
    return true;
}

bool Labels::load(ifstream &_input) {
    size_t length;
    _input.read((char*) &length, sizeof (length));
    
    resize(length);
    
    for (Label &label : (*this)) {
        label.load(_input);
    }
    
    return true;
}

bool Labels::save(ofstream &_output) const {
    size_t size = this->size();
    _output.write((char*) &size, sizeof(size));
    
    for (const Label &label : (*this)) {
        label.save(_output);
    }
    
    return true;
}

