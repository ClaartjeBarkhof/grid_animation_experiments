#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
//    nEntities = (int)ofRandom(4, 8);
    nEntities = 3;
    
    // Add all the rectangle entities
    for (int i = 0; i < nEntities; i++) {
        Entity tempEntity1, tempEntity2;
        
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
        
        allEntities.push_back(tempEntity1);
        allEntities.push_back(tempEntity2);
    }
    
    cout << allEntities.size() << endl;
    

}

//--------------------------------------------------------------
void ofApp::update(){
    
    for (int i = 0; i < allEntities.size(); i++) {
        allEntities[i].update();
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    
    for (int i = 0; i < allEntities.size(); i++) {
        allEntities[i].draw();
    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // Press 'r' for restart!
    if(key == 'r') {
        // Delete data in vectors
        allEntities.clear();
        
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
