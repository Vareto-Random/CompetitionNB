//
//  ImageSet.hpp
//  Competition
//
//  Created by Rafael Vareto on 10/22/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#ifndef Collection_hpp
#define Collection_hpp

#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/objdetect/objdetect.hpp>
//#include <opencv2/features2d/features2d.hpp>
//#include <opencv2/ml/ml.hpp>

#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/opencv/cv_image.h>

#include "Annotation.hpp"
#include "Cell.hpp"
#include "Component.hpp"
#include "Face.hpp"
#include "ImageSet.hpp"
#include "Label.hpp"

#include "ColorHistogram.hpp"
#include "CompoundLocalBinaryPattern.hpp"
#include "GaborFilter.hpp"
#include "HistogramOrientedGradient.hpp"
#include "LocalBinaryPattern.hpp"
#include "MeanIntensity.hpp"
#include "PatternOrientedEdgeMagnitude.hpp"

using namespace std;

#define SHIFT 10
#define GALLERY false
#define PROBE true

class Collection {
public:
    Collection();
    Collection(const map<string, cv::Mat> &_imageArray);
    Collection(const Collection &_collection);
    virtual ~Collection();
    
    bool blurFaces(const int _size = 3, const int _sigma = 5, bool _show = false);
    bool resizeFaces(const int _size);
    bool sharpenFaces();
    
    bool fetchCells(bool _show = false);
    bool fetchComponents(bool _show = false);
    bool fetchFaces(bool _show = false);
    bool fetchLandmarks(const string &_model, bool _show = false);
    
    map<string, vector<Cell> > getCellArray();
    map<string, vector<Component> > getComponentArray();
    map<string, Face> getFaceArray();
    map<string, cv::Mat> getImageArray();
    
    bool getAllFeatures(Matrix &_samples);
    bool getAllFeatures(Matrix &_samples, Labels &_labels, const bool _extra = false);
    bool getComponentsFeatures(vector<Matrix> &_samples);
    bool getComponentsFeatures(vector<Matrix> &_samples, Labels &_labels, const bool _extra = false);
    bool getFacesFeatures(Matrix &_samples, Labels &_labels, const bool _extra = false);
    
    bool setImageArray(const map<string, cv::Mat> &_imageArray);
    
private:
    void setUpBoolValues(bool _value = false);
    //void setUpDescritors();
    
    bool cellStatus, componentStatus, faceStatus;
    
    map<string, vector<Cell> > cellArray;
    map<string, vector<Component> > componentArray;
    map<string, Face> faceArray; //NOVO
    map<string, cv::Mat> imageArray;
    
    //vector<Descriptor *> descriptors;
};

#endif /* ImageSet_hpp */
