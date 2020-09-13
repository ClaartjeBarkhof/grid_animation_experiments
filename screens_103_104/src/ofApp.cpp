#include "ofApp.h"

int ARD_PIN_103 = 3;
int ARD_PIN_104 = 4;

//--------------------------------------------------------------
void ofApp::setup(){
    // SET-UP ARDUINO CONNECTION
    bSetupArduino    = false;    // flag so we setup arduino when its ready, you don't need to touch this :)
    ard.connect("/dev/tty.usbmodem14101", 57600); // /dev/tty.usbmodem14101
    ofAddListener(ard.EInitialized, this, &ofApp::setupArduino);
    
    // SET-UP BOTH SKETCHES
    setup_103();
    setup_104();
}

//--------------------------------------------------------------
void ofApp::update(){
    // UPDATEs BOTH SKETCHES
    update_103();
    update_104();
    
    // ARDUINO UPDATE
    ard.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    // DRAW APP 103, OTHER ONE IS DRAWN INDEPENDENTLY (104)
    draw_103();
}

//--------------------------------------------------------------
//--------------------------------------------------------------
// 103
//--------------------------------------------------------------
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

//--------------------------------------------------------------
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
void ofApp::clear_setup_103(){
   // Delete data in vectors
   allLayers1_103.clear();
   allLayers2_103.clear();
   allLayers3_103.clear();
   allLayers4_103.clear();
   
   setup_103();
}


//--------------------------------------------------------------
//--------------------------------------------------------------
// 104
//--------------------------------------------------------------
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
void ofApp::update_104(){
    
    for (int i = 0; i < allEntities_104.size(); i++) {
        allEntities_104[i].update();
    }

}

//--------------------------------------------------------------
void ofApp::draw_104(ofEventArgs & args){
    ofBackground(0);
    for (int i = 0; i < allEntities_104.size(); i++) {
        allEntities_104[i].draw();
    }
}

//--------------------------------------------------------------
void ofApp::clear_setup_104() {
    allEntities_104.clear();
    setup_104();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // Press 'r' for restart!
    if(key == '3') {
        clear_setup_103();
    }
    if(key == '4') {
        clear_setup_104();
    }
}


//--------------------------------------------------------------
//--------------------------------------------------------------
// ARDUINO STUFF
void ofApp::digitalPinChanged(const int & pinNum) {
    if (pinNum == ARD_PIN_103) {
        count_103 += 1;
        clear_setup_103();
        cout << "count 103: " << count_103 << endl;
    } else if (pinNum == ARD_PIN_104) {
        count_104 += 1;
        clear_setup_104();
        cout << "count 104: " << count_104 << endl;
    }
}

void ofApp::setupArduino(const int & version) {
    cout << "SET-UP ARDUINO" << endl;
    
    // remove listener because we don't need it anymore
    ofRemoveListener(ard.EInitialized, this, &ofApp::setupArduino);
    
    // it is now safe to send commands to the Arduino
    bSetupArduino = true;
    
    // print firmware name and version to the console
    ofLogNotice() << ard.getFirmwareName();
    ofLogNotice() << "firmata v" << ard.getMajorFirmwareVersion() << "." << ard.getMinorFirmwareVersion();
    
    ard.sendDigitalPinMode(ARD_PIN_103, ARD_INPUT_PULLUP); // for 103
    ard.sendDigitalPinMode(ARD_PIN_104, ARD_INPUT_PULLUP); // for 104

    ofAddListener(ard.EDigitalPinChanged, this, &ofApp::digitalPinChanged);
}
//--------------------------------------------------------------
//--------------------------------------------------------------
