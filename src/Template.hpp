//
//  Template.h
//  Competition
//
//  Created by Rafael Vareto on 11/7/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#ifndef Template_h
#define Template_h

template<typename T>
void save_list_sl(std::ofstream &output, std::vector<T> &list) {
    
    size_t size = list.size();
    
    output.write((char*) &size, sizeof (size));
    
    for (auto &el : list)
        el.save(output);
}

template<typename T>
void load_list_sl(std::ifstream &input, std::vector<T> &list) {
    
    size_t size = list.size();
    input.read((char*) &size, sizeof (size));
    
    list.resize(size);
    
    for (auto &el : list)
        el.load(input);
}

template<typename T>
void save_list_rw(std::ofstream &output, std::vector<T> &list) {
    
    size_t size = list.size();
    
    output.write((char*) &size, sizeof (size));
    
    for (auto &el : list)
        output.write((char*) &el, sizeof (el));
}

template<typename T>
void load_list_rw(std::ifstream &input, std::vector<T> &list) {
    
    size_t size = list.size();
    input.read((char*) &size, sizeof (size));
    
    list.resize(size);
    
    for (auto &el : list)
        input.read((char*) &el, sizeof (el));
}

#endif /* Template_h */
