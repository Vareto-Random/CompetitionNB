#
# This is a CMake makefile.  You can find the cmake utility and
# information about it at http://www.cmake.org
#
cmake_minimum_required(VERSION 2.8.4)

PROJECT(CompetitionNB.app)
SET(CMAKE_CXX_FLAGS_DISTRIBUTION "-O3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
include(src/dlib/cmake)

# Tell CMake to compile a program.  We do this with the ADD_EXECUTABLE()
# statement which takes the name of the output executable and then a list of
# .cpp files to compile.
ADD_EXECUTABLE(
CompetitionNB.app
src/Annotation.cpp
src/Cell.cpp
src/Collection.cpp
src/ColorHistogram.cpp
src/Component.cpp
src/CompoundLocalBinaryPattern.cpp
src/Face.cpp
src/GaborFilter.cpp
src/HistogramOrientedGradient.cpp
src/ImageSet.cpp
src/Label.cpp
src/LocalBinaryPattern.cpp
src/Matrix.cpp
src/MeanIntensity.cpp
src/PatternOrientedEdgeMagnitude.cpp
src/PLSclassifier.cpp
src/PLSregression.cpp
src/SlideWindow.cpp
src/Useful.cpp
src/UStandardDeviation.cpp
src/ZeroMean.cpp
src/ZeroScore.cpp
src/main.cpp
)

# Then we tell it to link with dlib.
TARGET_LINK_LIBRARIES(CompetitionNB.app ${OpenCV_LIBS} dlib)
