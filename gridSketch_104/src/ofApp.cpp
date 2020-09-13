#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    setup_104();

}

void ofApp::setup_104(){
    nEntities_104 = 3;
    
    // Add all the rectangle entities
    for (int i = 0; i < nEntities_104; i++) {
        Entity_104 tempEntity1, tempEntity2;
        
        float percPosRef = ofRandom(1.0);
        bool vertical_;
        if (ofRandom(1.0) < 0.5) {
            vertical_ = true;
        } else {
            vertical_ = false;
        }
        
        bool firstOfAll;
        
        if (i == 0) {
            firstOfAll = true;
            percPosRef = 0.0;
        } else {
            firstOfAll = false;
        }
        
        tempEntity1.setup(percPosRef, vertical_, true, firstOfAll);
        tempEntity2.setup(percPosRef, vertical_, false, firstOfAll);
        
        allEntities_104.push_back(tempEntity1);
        allEntities_104.push_back(tempEntity2);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    update_104();

}

void ofApp::update_104(){
    
    for (int i = 0; i < allEntities_104.size(); i++) {
        allEntities_104[i].update();
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    draw_104();
}

void ofApp::draw_104(){
    ofBackground(0);
    for (int i = 0; i < allEntities_104.size(); i++) {
        allEntities_104[i].draw();
    }
}

void ofApp::clear_setup_104() {
    allEntities_104.clear();
    setup_104();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // Press 'r' for restart!
    if(key == 'r') {
        clear_setup_104();
    }
}
