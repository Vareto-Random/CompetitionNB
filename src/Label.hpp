//
//  Label.hpp
//  Competition
//
//  Created by Rafael Vareto on 11/7/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#ifndef Label_hpp
#define Label_hpp

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

class Label {
public:
    Label();
    Label(const string &_id, const bool _extra = false);
    void save(ofstream &_output) const;
    void load(ifstream &_input);
    
    const bool getExtra() const;
    const string getId() const;
    
    bool setExtra(const bool _extra);
    bool setId(const string _id);
    
private:
    bool extra;
    string id;
};


class Labels : public vector<Label> {
public:
    bool load(ifstream &_input);
    bool save(ofstream &_output) const;
};

#endif /* Label_hpp */
