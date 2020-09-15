#include "Layer.h"
Layer::Layer(){
}

void Layer::setup(int layerType_, int nCols_, int nRows_) {
    cout << "SETUP LAYER TYPE: " << layerType_ << "nCols: " << nCols_ << "nRows: " << nRows_;
    
    blend_modes = {OF_BLENDMODE_SUBTRACT, OF_BLENDMODE_MULTIPLY, OF_BLENDMODE_ALPHA, OF_BLENDMODE_SCREEN, OF_BLENDMODE_ADD};
    
    if (layerType == 2) {
        layerColor = ofColor(ofRandom(150), ofRandom(150), ofRandom(150));
        blendMode_2 = blend_modes[(int)ofRandom(blend_modes.size())];
    } else {
        layerColor = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
    }
    
    layerType = layerType_;
    nCols = nCols_;
    nRows = nRows_;
}

void Layer::update(bool signal) {
    if (layerType == 1) {
        update_1(signal);
    }
    if (layerType == 2) {
        update_2(signal);
    }
    if (layerType == 3) {
        update_3(signal);
    }
}

void Layer::draw(){
    if (layerType == 1) {
        draw_1();
    }
    if (layerType == 2) {
        draw_2();
    }
    if (layerType == 3) {
        draw_3();
    }
}

void Layer::update_1(bool signal) {
    
}

void Layer::update_2(bool signal) {
//    cout << "UPDATE 2" << endl;
    float max_rect_size = ofGetWidth()*1.3;
    float grow_scale = 1.02;
    
    // If new onset, new rect
    if (signal) {
        vector<float> rect = {0., 0., 10., 10.};
        myRects_2.push_back(rect);
    }

    // Record which rectangles to erase
    vector<int> erase_rects;

    // Shrink the rects over time, erase when size ~ 0
    for(int i = 0; i < myRects_2.size(); i++) {
        // Check size if larger than thresh, store their index for removal
        if ((myRects_2[i][2] > max_rect_size) || (myRects_2[i][3] > max_rect_size)) {
            erase_rects.push_back(i);
        }

        // Scale with and height
        myRects_2[i][2] *= grow_scale;
        myRects_2[i][3] *= grow_scale;

        // Calculate x, y upperleft
        myRects_2[i][0] = (ofGetWidth() / 2.)  - (myRects_2[i][2] / 2.);
        myRects_2[i][1] = (ofGetHeight() / 2.) - (myRects_2[i][3] / 2.);
    }

    // Erase rectangles that became too big
    for(int i = 0; i<erase_rects.size(); i++) {
        myRects_2.erase(myRects_2.begin() + erase_rects[i]);
    }
}

void Layer::update_3(bool signal) {
    float min_rect_size = 100.;
    float shrink_scale = 0.98;
    
    // If new onset, new rect
    if (signal) {
        vector<float> rect = {0., 0., (float)ofGetWidth(), (float)ofGetHeight()};
        myRects_3.push_back(rect);
    }
    
    // Record which rectangles to erase
    vector<int> erase_rects;
    
    // Shrink the rects over time, erase when size ~ 0
    for(int i = 0; i<myRects_3.size(); i++) {
        // Check size if smaller than thresh, store their index for removal
        if ((myRects_3[i][2] < min_rect_size) || (myRects_3[i][3] < min_rect_size)) {
            erase_rects.push_back(i);
        }

        // Scale with and height
        myRects_3[i][2] *= shrink_scale;
        myRects_3[i][3] *= shrink_scale;

        // Calculate x, y upperleft
        myRects_3[i][0] = (ofGetWidth() / 2.)  - (myRects_3[i][2] / 2.);
        myRects_3[i][1] = (ofGetHeight() / 2.) - (myRects_3[i][3] / 2.);
    }
    
    // Erase rectangles that became too small
    for(int i = 0; i<erase_rects.size(); i++) {
        myRects_3.erase(myRects_3.begin() + erase_rects[i]);
    }
}

void Layer::draw_1() {
    
}

void Layer::draw_2() {
//    cout << "DRAW 2" << endl;
    
    float w_col = ofGetWidth() / nCols;
    float h_row = ofGetHeight() / nRows;
    
    // No fill and red color
    ofSetColor(layerColor);
    ofFill();
    
    for(int r = 0; r<nRows; r++) {
        for(int c = 0; c<nCols; c++) {
            for(int i = 0; i<myRects_2.size(); i++) {
                if ((i % 2) == 0) {
                    ofEnableBlendMode(blendMode_2);
                } else {
                    ofDisableBlendMode();
                    ofSetColor(ofColor(0, 0, 0));
                }
                ofSetLineWidth(0);
                float x_frac = myRects_2[i][0] / ofGetWidth();
                float y_frac = myRects_2[i][1] / ofGetHeight();
                float w_frac = myRects_2[i][2] / ofGetWidth();
                float h_frac = myRects_2[i][3] / ofGetHeight();
                float x = (c*w_col) + (x_frac*w_col);
                float y = (r*h_row) + (y_frac*h_row);
                float w = w_col * w_frac;
                float h = h_row * h_frac;
                ofDrawRectangle(x, y, w, h);
            }
        }
    }
    ofDisableBlendMode();
}

void Layer::draw_3() {
    float w_col = ofGetWidth() / nCols;
    float h_row = ofGetHeight() / nRows;
    
    // No fill and red color
    ofNoFill();
    ofSetColor(layerColor);
    
    for(int r = 0; r<nRows; r++) {
        for(int c = 0; c<nCols; c++) {
            for(int i = 0; i<myRects_3.size(); i++) {
                // Check what percentage the width of the rect is
//                float p =  myRects_3[i][2] / ofGetWidth();
                ofSetLineWidth(1);
                float x_frac = myRects_3[i][0] / ofGetWidth();
                float y_frac = myRects_3[i][1] / ofGetHeight();
                float w_frac = myRects_3[i][2] / ofGetWidth();
                float h_frac = myRects_3[i][3] / ofGetHeight();
                float x = (c*w_col) + (x_frac*w_col);
                float y = (r*h_row) + (y_frac*h_row);
                float w = w_col * w_frac;
                float h = h_row * h_frac;
                ofDrawRectangle(x, y, w, h);
            }
        }
    }
    
    
}
