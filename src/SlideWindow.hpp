//
//  SlideWindow.hpp
//  Competition
//
//  Created by Rafael Vareto on 11/6/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#ifndef SlideWindow_hpp
#define SlideWindow_hpp

#include <cassert>
#include <iostream>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/opencv.hpp>

using namespace std;

typedef cv::Mat Image;

class SlideWindow {
public:
    static void slideWindow(const Image &_image, const cv::Size &_size, const cv::Size &_stride, std::function<void(const cv::Rect&)> _callback);
    
    static void slideWindow(const cv::Size &_image, const cv::Size &_size, const cv::Size &_stride, std::function<void(const cv::Rect&)> _callback);
    
    static void slideWindow(const Image &_image, const cv::Size &_size, const cv::Size &_stride, std::function<void(const Image&)> _callback);
    
    static void slideWindow(const Image &_image, const cv::Size &_size, const cv::Size &_stride, std::function<void(Image&)> _callback);
};

#endif /* SlideWindow_hpp */
