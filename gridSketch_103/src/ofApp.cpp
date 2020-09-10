#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    balance = ofRandom(0, TWO_PI);
    
    fbo1.allocate( ofGetWidth(), ofGetHeight());
    fbo2.allocate( ofGetWidth(), ofGetHeight());
    fbo3.allocate( ofGetWidth(), ofGetHeight());
    fbo4.allocate( ofGetWidth(), ofGetHeight());

//    setup_layers(allLayers1);
//    setup_layers(allLayers2);
//
    nLayers1 = (int)ofRandom(1, 3);
    for(int i = 0; i < nLayers1; i++) {
        Layer tempLayer;
        tempLayer.setup(i);
        allLayers1.push_back(tempLayer);
    }
    
    nLayers2 = (int)ofRandom(1, 3);
    for(int i = 0; i < nLayers2; i++) {
        Layer tempLayer;
        tempLayer.setup(i);
        allLayers2.push_back(tempLayer);
    }
    
    nLayers3 = (int)ofRandom(1, 3);
    for(int i = 0; i < nLayers3; i++) {
        Layer tempLayer;
        tempLayer.setup(i);
        allLayers3.push_back(tempLayer);
    }
    
    nLayers4 = (int)ofRandom(1, 3);
    for(int i = 0; i < nLayers4; i++) {
        Layer tempLayer;
        tempLayer.setup(i);
        allLayers4.push_back(tempLayer);
    }

    
}

//void ofApp::setup_layers(vector<Layer> layerVector) {
//    nLayers = (int)ofRandom(1, 3);
//
//    for(int i = 0; i < nLayers; i++) {
//        Layer tempLayer;
//        tempLayer.setup(i);
//        layerVector.push_back(tempLayer);
//    }
//}

//--------------------------------------------------------------
void ofApp::update(){
    balance += 0.01;
    
    for(int i = 0; i < nLayers1; i++) {
        allLayers1[i].update();
    }
    for(int i = 0; i < nLayers2; i++) {
        allLayers2[i].update();
    }
    for(int i = 0; i < nLayers2; i++) {
        allLayers3[i].update();
    }
    for(int i = 0; i < nLayers2; i++) {
        allLayers4[i].update();
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    fbo1.begin();
    for(int i = 0; i < nLayers1; i++) {
        allLayers1[i].draw();
    }
    fbo1.end();
    
    fbo2.begin();
    for(int i = 0; i < nLayers2; i++) {
        allLayers2[i].draw();
    }
    fbo2.end();
    
    fbo3.begin();
    for(int i = 0; i < nLayers3; i++) {
        allLayers3[i].draw();
    }
    fbo3.end();
    
    fbo4.begin();
    for(int i = 0; i < nLayers4; i++) {
        allLayers4[i].draw();
    }
    fbo4.end();
    
    ofSetColor( 255, 255, 255 );
    
//    float shareFirst = 0.2 * sin(balance) + 0.5;
    
//    float posY = (0.2 * sin(balance) + 0.5) * ofGetHeight();
//    float posX = (0.2 * cos(balance) + 0.5) * ofGetWidth();
    
    float posY = ofGetMouseY();
    float posX = ofGetMouseX();
    
    fbo1.draw( 0,    0,    posX,               posY);
    fbo2.draw( posX, 0,    ofGetWidth()-posX,  posY);
    fbo3.draw( 0,    posY, posX,               ofGetHeight()-posY);
    fbo4.draw( posX, posY, ofGetWidth()-posX,  ofGetHeight()-posY);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // Press 'r' for restart!
    if(key == 'r') {
        // Delete data in vectors
        allLayers1.clear();
        allLayers2.clear();
        allLayers3.clear();
        allLayers4.clear();
        
        setup();
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
