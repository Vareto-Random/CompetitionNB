//
//  main.cpp
//  Competition
//
//  Created by Rafael Vareto on 10/22/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#include <iostream>

#include "Annotation.hpp"
#include "Cell.hpp"
#include "Collection.hpp"
#include "ImageSet.hpp"
#include "Useful.hpp"

#include "PLSclassifier.hpp"

#include "Label.hpp"
#include "Matrix.hpp"
#include "PLSregression.hpp"
#include "SlideWindow.hpp"
#include "ZeroScore.hpp"

#define CROP true
#define MODEL "training.model"
#define PREDICTOR "shape_predictor.dat"
#define SHOW false

using namespace std;

int main(int argc, const char * argv[]) {
    string path = argv[1];
    string note = argv[2];

    int count;
    Labels galleryLabels, probeLabels;
    Matrix gallerySamples, probeSamples, responses;
    PLSclassifier model(5);
    ZeroScore zscore;

    if ( (argc == 4) and (strcmp (argv[3],"--train") == 0) ) //TRAINING
    {
//        cout << "----Reading Gallery----\n";
//        ImageSet gallery = ImageSet(note, path);
//        gallery.readNotes(CROP);
//        gallery.increaseWindowSize(1.15);
//        gallery.loadFaces(CROP); //string("_f.jpg")
//
//        cout << "----Generating Train Collection----\n";
//        Collection train = Collection(gallery.getImageArray());
//        train.resizeFaces(256);
//        cout << "\tGallery Landmark Identification\n";
//        train.fetchLandmarks(string(PREDICTOR), SHOW);
//        cout << "\tGallery Cells Fetching\n";
//        train.fetchCells(SHOW);
//        cout << "\tGallery Components Fetching\n";
//        train.fetchComponents(SHOW);
//        cout << "\tGallery Face Fetching\n";
//        train.fetchFaces(SHOW);
//
//        cout << "\tAll Features Fetching\n";
//        train.getAllFeatures(gallerySamples, galleryLabels);
//        cout << "ROWS: " << gallerySamples.rows << " - COLS: " << gallerySamples.cols << endl;
        
        Useful::readCNNfeatures("dataset/Features/Gallery_34.txt", "dataset/annotations_GalleryImages.txt", gallerySamples, galleryLabels);
        cout << "ROWS: " << gallerySamples.rows << " - COLS: " << gallerySamples.cols << endl;

        cout << "\tWriting features to file: features_" + note.substr(note.find_last_of("/") + 1) << endl;
        ofstream outfile;
        outfile.open("features_" + note.substr(note.find_last_of("/") + 1));
        for (unsigned int outer = 0; outer < gallerySamples.rows; outer++) {        
            for (unsigned int inner = 0; inner < gallerySamples.cols; inner++) {
                outfile << *gallerySamples.row(outer).col(inner)[0] << " ";
            }
            outfile << endl;
        }
        outfile.close();

        cout << "\tWriting features to file: labels_" + note.substr(note.find_last_of("/") + 1) << endl;
        outfile.open("labels_" + note.substr(note.find_last_of("/") + 1));
        for (unsigned int index = 0; index < galleryLabels.size(); index++) {
            outfile << galleryLabels[index].getId() << endl;
        }
        outfile.close();  

//        cout << endl << "Quitting..." << endl;
//        return 0;

        cout << "----Training----\n";
        zscore.trainNorm(gallerySamples);
        model.train(gallerySamples, galleryLabels);

        cout << "----Saving Training----\n";
        string filename = MODEL;
        ofstream output(filename);
        assert(output.is_open());

        gallerySamples.save(output);
        galleryLabels.save(output);
        zscore.save(output);
        model.save(output);

        cout << "\tSignature:\n";
        cout << "\t- " << gallerySamples(0, 0) << "\n";
        cout << "\t- " << galleryLabels.back().getId() << "\n";
        cout << "\t- " << model.models.back().regression(0, 0) << "\n";
    } 
    else if (argc == 3) //TESTING
    {
        cout << "----Loading Training----\n";
        string filename = MODEL;
        ifstream input(filename);
        assert(input.is_open());

        gallerySamples.load(input);
        galleryLabels.load(input);
        zscore.load(input);
        model.load(input);

        cout << "\tSignature:\n";
        cout << "\t- " << gallerySamples(0, 0) << "\n";
        cout << "\t- " << galleryLabels.back().getId() << "\n";
        cout << "\t- " << model.models.back().regression(0, 0) << "\n";

//        cout << "----Reading Probe----\n";
//        ImageSet probe = ImageSet(note, path);
//        probe.readNotes(CROP);
//        probe.increaseWindowSize(1.15);
//        probe.loadFaces(CROP);
//        
//        cout << "----Generating Test Collection----\n";
//        Collection test = Collection(probe.getImageArray());
//        test.resizeFaces(256);
//        test.sharpenFaces();
//        cout << "\tProbe Landmark Identification\n";
//        test.fetchLandmarks(string(PREDICTOR), SHOW);
//        cout << "\tProbe Cells Fetching\n";
//        test.fetchCells(SHOW);
//        cout << "\tProbe Components Fetching\n";
//        test.fetchComponents(SHOW);
//        cout << "\tProbe Face Fetching\n";
//        test.fetchFaces(SHOW);
        
        cout << "\tAll Features Fetching\n";
        // test.getAllFeatures(probeSamples, probeLabels);
        vector<string> subjects = Useful::readCNNfeatures("dataset/Features/Evaluation_34.txt", "dataset/annotations_EvaluationImages.txt", probeSamples, probeLabels);
        cout << "ROWS: " << probeSamples.rows << " - COLS: " << probeSamples.cols << endl;

        vector<int> hits(subjects.size(), 0);
        vector<pair<string, float> > ranking( subjects.size() );

        cout << "\tWriting features to file: features_" + note.substr(note.find_last_of("/") + 1) << endl;
        ofstream outfile;
        outfile.open("features_" + note.substr(note.find_last_of("/") + 1));
        for (unsigned int outer = 0; outer < probeSamples.rows; outer++) {        
            for (unsigned int inner = 0; inner < probeSamples.cols; inner++) {
                outfile << *probeSamples.row(outer).col(inner)[0] << " ";
            }
            outfile << endl;
        }
        outfile.close();

        cout << "\tWriting features to file: labels_" + note.substr(note.find_last_of("/") + 1) << endl;
        outfile.open("labels_" + note.substr(note.find_last_of("/") + 1));
        for (unsigned int index = 0; index < probeLabels.size(); index++) {
            outfile << probeLabels[index].getId() << endl;
        }
        outfile.close(); 

        cout << "----Testing----\n";
        zscore.norm(probeSamples);
        model.respond(probeSamples,responses);

        cout << "----Saving File----\n";
        Useful::save2file(model, responses, probeLabels);
        
        cout << "----CMC Ranking----\n";
        count = 0;
        for (int outer = 0; outer < responses.rows; outer++) {
            Matrix response = responses.row(outer);
            
            //assert( response.cols == ranking.size() );
            for (int inner = 0; inner < ranking.size(); inner++) {
                ranking[inner].first = model.labels[inner].getId();
                ranking[inner].second = response(inner);
            }
            
            sort(ranking.begin(), ranking.end(), [](const pair<string, float> &a, const pair<string, float> &b) {
                return a.second > b.second;
            });
            
            for (int rank = 0; rank < ranking.size(); rank++) {
                for (int index = 0; index <= rank; index++) {
                    if(ranking[index].first == probeLabels[outer].getId()) {
                        hits[rank]++;
                        break;
                    }
                }
            }
            count++;
        }
        
        cout << "\tX\tY\n";
        for (int index = 0; index < hits.size(); index++) {
            cout << "\t" << index + 1 << "\t" <<  hits[index] / (float) count << "\n";
        }
    } 
    else // WRONG ARGUMENTS
    {
        cerr << "You have inserted the wrong parameters:" << endl
            << "Executable [PATH TO IMAGES] [ANNOTATION FILE]" << endl;
    }
    
    return 0;
}
