#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    setup_103();
}

void ofApp::setup_103() {    
    bgColor_103 = ofColor(ofRandom(100), ofRandom(100), ofRandom(100));
    
    fbo1_103.allocate( ofGetWidth(), ofGetHeight());
    fbo2_103.allocate( ofGetWidth(), ofGetHeight());
    fbo3_103.allocate( ofGetWidth(), ofGetHeight());
    fbo4_103.allocate( ofGetWidth(), ofGetHeight());

    nLayers1_103 = (int)ofRandom(1, 3);
    for(int i = 0; i < nLayers1_103; i++) {
        Layer_103 tempLayer;
        tempLayer.setup(i);
        allLayers1_103.push_back(tempLayer);
    }
    
    nLayers2_103 = (int)ofRandom(1, 3);
    for(int i = 0; i < nLayers2_103; i++) {
        Layer_103 tempLayer;
        tempLayer.setup(i);
        allLayers2_103.push_back(tempLayer);
    }
    
    nLayers3_103 = (int)ofRandom(1, 3);
    for(int i = 0; i < nLayers3_103; i++) {
        Layer_103 tempLayer;
        tempLayer.setup(i);
        allLayers3_103.push_back(tempLayer);
    }
    
    nLayers4_103 = (int)ofRandom(1, 3);
    for(int i = 0; i < nLayers4_103; i++) {
        Layer_103 tempLayer;
        tempLayer.setup(i);
        allLayers4_103.push_back(tempLayer);
    }
}

//--------------------------------------------------------------
void ofApp::update_103(){
    for(int i = 0; i < nLayers1_103; i++) {
        allLayers1_103[i].update();
    }
    for(int i = 0; i < nLayers2_103; i++) {
        allLayers2_103[i].update();
    }
    for(int i = 0; i < nLayers3_103; i++) {
        allLayers3_103[i].update();
    }
    for(int i = 0; i < nLayers4_103; i++) {
        allLayers4_103[i].update();
    }
    
}

void ofApp::update() {
    update_103();
}

void ofApp::draw_103() {
    ofBackground(bgColor_103);
    fbo1_103.begin();
     for(int i = 0; i < nLayers1_103; i++) {
         allLayers1_103[i].draw();
     }
     fbo1_103.end();
     
     fbo2_103.begin();
     for(int i = 0; i < nLayers2_103; i++) {
         allLayers2_103[i].draw();
     }
     fbo2_103.end();
     
     fbo3_103.begin();
     for(int i = 0; i < nLayers3_103; i++) {
         allLayers3_103[i].draw();
     }
     fbo3_103.end();
     
     fbo4_103.begin();
     for(int i = 0; i < nLayers4_103; i++) {
         allLayers4_103[i].draw();
     }
     fbo4_103.end();
     
     ofSetColor( 255, 255, 255 );
       
    float posY = ofMap( ofNoise( ofGetElapsedTimef()/20.0, 1000), 0, 1,
                       ofGetHeight()*0.1, ofGetHeight()*0.9);
    float posX = ofMap( ofNoise( ofGetElapsedTimef()/20.0, -1000), 0, 1,
                       ofGetWidth()*0.1, ofGetWidth()*0.9);
     
     fbo1_103.draw( 0,    0,    posX,               posY);
     fbo2_103.draw( posX, 0,    ofGetWidth()-posX,  posY);
     fbo3_103.draw( 0,    posY, posX,               ofGetHeight()-posY);
     fbo4_103.draw( posX, posY, ofGetWidth()-posX,  ofGetHeight()-posY);
}

//--------------------------------------------------------------
void ofApp::draw(){
    draw_103();
 }

//--------------------------------------------------------------
void ofApp::clear_setup_103(){
    // Delete data in vectors
    allLayers1_103.clear();
    allLayers2_103.clear();
    allLayers3_103.clear();
    allLayers4_103.clear();
    
    setup_103();
 }

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // Press 'r' for restart!
    if(key == 'r') {
        clear_setup_103();
    }
}
