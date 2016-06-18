//
//  SlideWindow.cpp
//  Competition
//
//  Created by Rafael Vareto on 11/6/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#include "SlideWindow.hpp"

void SlideWindow::slideWindow(const cv::Size &_image, const cv::Size &_size, const cv::Size &_stride, std::function<void(const cv::Rect&)> _callback) {
    
    assert(_size.width <= _image.width && _size.height <= _image.height);
    
    for (cv::Rect window(0, 0, _size.width, _size.height); window.y <= _image.height - window.height; window.y += _stride.height) {
        for (window.x = 0; window.x <= _image.width - window.width; window.x += _stride.width) {
            _callback(window);
        }
    }
}

void SlideWindow::slideWindow(const Image &_image, const cv::Size &_size, const cv::Size &_stride, std::function<void(const cv::Rect&) > _callback) {
    SlideWindow::slideWindow(cv::Size(_image.cols, _image.rows), _size, _stride, _callback);
}

void SlideWindow::slideWindow(const Image &_image, const cv::Size &_size, const cv::Size &_stride, std::function<void(const Image&)> _callback) {
    SlideWindow::slideWindow(
                             cv::Size(_image.cols, _image.rows), _size, _stride,
                             [&](const cv::Rect & window) {
                                 _callback(_image(window));
                             });
}

void SlideWindow::slideWindow(const Image &_image, const cv::Size &_size, const cv::Size &_stride, std::function<void(Image&)> _callback) {
    SlideWindow::slideWindow(
                             cv::Size(_image.cols, _image.rows), _size, _stride,
                             [&](const cv::Rect & window) {
                                 Image crop = _image(window);
                                 _callback(crop);
                             });
}