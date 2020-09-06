#include "Layer.h"
Layer::Layer(){
}

void Layer::setup(int bpm){
    layerColor = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
}

void Layer::update(bool gotonset){
    float min_rect_size = 100.;
    float shrink_scale = 0.98;
    
    // If new onset, new rect
    if (gotonset) {
        vector<float> rect = {0., 0., (float)ofGetWidth(), (float)ofGetHeight()};
        myRects.push_back(rect);
    }
    
    // Record which rectangles to erase
    vector<int> erase_rects;
    
    // Shrink the rects over time, erase when size ~ 0
    for(int i = 0; i<myRects.size(); i++) {
        // Check size if smaller than thresh, store their index for removal
        if ((myRects[i][2] < min_rect_size) || (myRects[i][3] < min_rect_size)) {
            erase_rects.push_back(i);
        }

        // Scale with and height
        myRects[i][2] *= shrink_scale;
        myRects[i][3] *= shrink_scale;

        // Calculate x, y upperleft
        myRects[i][0] = (ofGetWidth() / 2.)  - (myRects[i][2] / 2.);
        myRects[i][1] = (ofGetHeight() / 2.) - (myRects[i][3] / 2.);
    }
    
    // Erase rectangles that became too small
    for(int i = 0; i<erase_rects.size(); i++) {
        myRects.erase(myRects.begin() + erase_rects[i]);
    }
    
}

void Layer::draw(bool gotbeat){
    // No fill and red color
    ofNoFill();
    ofSetColor(layerColor);
    
    for(int i = 0; i<myRects.size(); i++) {
        // Check what percentage the width of the rect is
        float p =  myRects[i][2] / ofGetWidth();
        ofSetLineWidth(3);
        ofDrawRectangle(myRects[i][0], myRects[i][1], myRects[i][2], myRects[i][3]);
    }

}
