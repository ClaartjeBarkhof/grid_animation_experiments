#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // "Globals"
    min_n_lines = 5;
    max_n_lines = 12;
    min_side_length = 0.15*ofGetHeight(); // min width in scale 1.0, it scales to x 2.4
    max_side_length = 0.5*ofGetHeight();
    min_line_width = 5;
    max_line_width = 10;
    min_n_recs = 3;
    max_n_recs = 7;
    
    n_recs = (int)ofRandom(min_n_recs, max_n_recs+1);
    
    backgroundColour.set(ofRandom(255),ofRandom(255),ofRandom(255));
    
    // Todo: set init params
    background_rect.setup(ofGetWidth(), ofGetHeight(),
                          min_line_width, max_line_width,
                          min_n_lines, max_n_lines);

    // Add all the rectangle entities
    for (int i = 0; i < n_recs; i++) {
        Entity tempRect;
        tempRect.setup(min_side_length, max_side_length,
                       min_line_width, max_line_width,
                       min_n_lines, max_n_lines);
        rects.push_back(tempRect);
    }

}

//--------------------------------------------------------------
void ofApp::update(){
    // Update all rects, including the background rect
    background_rect.update();
    
    for(int i = 0; i < n_recs; i++) {
      rects[i].update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    // Set blending mode off and draw a black background
    ofDisableBlendMode();
    ofBackground(backgroundColour);
    
    
    // Draw all rects, including the background rect
    background_rect.draw();
    
    for(int i = 0; i < n_recs; i++) {
      rects[i].draw();
    }
    
    // Draw some bit strings on screen for testing
    string info = "fps: " + ofToString(ofGetFrameRate(),2);
    ofDisableBlendMode();
    ofSetColor(255, 255, 255);
    ofDrawBitmapString(info, 10, 20);
    
    ofDrawBitmapString("Press 'r' for random restart!" , 10, 60);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // Press 'r' for restart!
    if(key == 'r') {
        // Delete data in vectors
        rects.clear();
        
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