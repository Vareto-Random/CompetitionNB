//
//  ImageSet.hpp
//  Competition
//
//  Created by Rafael Vareto on 10/22/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#ifndef ImageSet_hpp
#define ImageSet_hpp

#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <string>
#include <vector>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "Annotation.hpp"

using namespace std;

class ImageSet {
public:
    ImageSet();
    ImageSet(const string &_file, const string &_path);
    ImageSet(const ImageSet &_imageSet);
    virtual ~ImageSet();
    
    void setFile(string &_file);
    void setPath(string &_path);
    
    bool increaseWindowSize(const double _percent);
    
    bool loadFaces(const bool _crop = true);
    bool loadFaces(const string &_filter, const bool _crop = true);
    bool readNotes(const bool _crop = true);
    bool readNotes(const string &_file, const bool _crop = true);
    
    set<string> getSamplesSet();
    set<string> getSubjectsSet();
    
    vector<string> getSamples();
    vector<string> getSubjects();
    
    vector<Annotation> getDataArray();
    map<string, cv::Mat> getImageArray();
    
private:
    bool loadFaces(const vector<Annotation> &_dataArray, const string &_path, const bool _crop = true);
    bool loadFaces(const vector<Annotation> &_dataArray, const string &_path, const string &_filter, const bool _crop = true);
    
    bool runFile;
    bool runPath;
    
    string file;
    string path;
    
    map<string, cv::Mat> imageArray;
    set<string> samples;
    set<string> subjects;
    vector<Annotation> dataArray;
};

#endif /* ImageSet_hpp */
