#include "ofApp.h"

int ARD_PIN_101 = 3;
int ARD_PIN_102 = 4;

//--------------------------------------------------------------
void ofApp::setup(){
    // SET-UP ARDUINO CONNECTION
    bSetupArduino    = false;    // flag so we setup arduino when its ready, you don't need to touch this :)
    ard.connect("/dev/tty.usbmodem14101", 57600);
    ofAddListener(ard.EInitialized, this, &ofApp::setupArduino);
    
    // SET-UP BOTH SKETCHES
    setup_101();
    setup_102();
}

//--------------------------------------------------------------
void ofApp::update(){
    // UPDATEs BOTH SKETCHES
    update_101();
    update_102();
    
    // ARDUINO UPDATE
    ard.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    // DRAW APP 101, OTHER ONE IS DRAWN INDEPENDENTLY
    draw_101();
}

//--------------------------------------------------------------
//--------------------------------------------------------------
// 101
//--------------------------------------------------------------
void ofApp::update_101(){
    for(int i = 0; i<allEntities_101.size(); i++) {
        allEntities_101[i].update();
    }
}

void ofApp::setup_101() {
    // GLOBALS
    max_ent_cell_101 = (int)ofRandom(1, 5);
    min_ent_cell_101 = (int)ofRandom(2);
    
    // Increas the chance of more cols than row or inversely
    if (ofRandom(1.0) > 0.5) {
        n_cols_101 = (int)ofRandom(1, 8);
        n_rows_101 = (int)ofRandom(1, 4);
    } else {
        n_cols_101 = (int)ofRandom(1, 4);
        n_rows_101 = (int)ofRandom(1, 8);
    }

    // Width of the cells or small grids
    width_cell_101 = ofGetWidth() / n_cols_101;
    height_cell_101 = ofGetHeight() / n_rows_101;
    
    // Background colors
    for (int i = 0; i < n_rows_101 * n_cols_101; i++) {
        background_colors_101.push_back(ofColor(ofRandom(120),ofRandom(120),ofRandom(120)));
    }
    
    // Keep track for that cell which entities (indices) belong to it
    int ent_counter = 0;
    entity_per_cell_101.resize(n_cols_101 * n_rows_101);
    
    // For every cell (row, col): add a random number of entities
    for (int r = 0; r < n_rows_101; r++){
        for(int c = 0; c < n_cols_101; c++) {

            // Row, col corresponds to cell i
            int cell_i = getCell_101(r, c, n_cols_101);
            
            // Number of entities in this cell
            int n_ents = (int)ofRandom(min_ent_cell_101, max_ent_cell_101);
            
            // Keep track for that cell which entities (indices) belong to it
            entity_per_cell_101[cell_i].resize(n_ents);
            
            // Add the entities
            for (int n = 0; n <= n_ents; n++) {

                // Add the entity to the vector of entities
                Entity_101 tempEnt;
                tempEnt.setup(cell_i, n_rows_101, n_cols_101);
                allEntities_101.push_back(tempEnt);
                
                // Keep track for that cell which entities (indices) belong to it
                entity_per_cell_101[cell_i].push_back(ent_counter);
                
                // Count the entities total
                ent_counter++;
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw_101(){
//    ofBackground(0);
    ofSetColor(0);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    
    // Iterate over cells (rows and colls)
    int cell_i = 0;
    for (int r = 0; r < n_rows_101; r++){
        for(int c = 0; c < n_cols_101; c++) {
            
            ofDisableBlendMode();
            
            // Draw background of cell
            ofSetColor(background_colors_101[cell_i]);
            ofDrawRectangle(c * width_cell_101, r * height_cell_101, width_cell_101, height_cell_101);
            
            // Draw entities in cell
            for(int n = 0; n < entity_per_cell_101[cell_i].size(); n++) {
                allEntities_101[entity_per_cell_101[cell_i][n]].draw();
            }
            
            cell_i++;
        }
    }
    
    // Draw some bit strings on screen for testing
    string info = "101 fps: " + ofToString(ofGetFrameRate(),2);
    ofDisableBlendMode();
    ofSetColor(255, 255, 255);
    ofDrawBitmapString(info, 10, 20);
}

void ofApp::clear_setup_101() {
    // Delete data in vectors
    background_colors_101.clear();
    entity_per_cell_101.clear();
    allEntities_101.clear();
    
    setup_101();
}

int ofApp::getCell_101(int row, int col, int n_cols) {
    int cell = (int)(row * n_cols) + col;
    return cell;
}

//--------------------------------------------------------------
//--------------------------------------------------------------
// 102
//--------------------------------------------------------------
void ofApp::setup_102(){
    // "Globals"
    min_n_lines_102 = 5;
    max_n_lines_102 = 12;
    min_side_length_102 = 0.15*ofGetHeight(); // min width in scale 1.0, it scales to x 2.4
    max_side_length_102 = 0.5*ofGetHeight();
    min_line_width_102 = 5;
    max_line_width_102 = 10;
    min_n_recs_102 = 3;
    max_n_recs_102 = 7;
    
    n_recs_102 = (int)ofRandom(min_n_recs_102, max_n_recs_102+1);
    
    backgroundColour_102.set(ofRandom(255),ofRandom(255),ofRandom(255));
    
    // Todo: set init params
    background_rect_102.setup(ofGetWidth(), ofGetHeight(),
                          min_line_width_102, max_line_width_102,
                          min_n_lines_102, max_n_lines_102);

    // Add all the rectangle entities
    for (int i = 0; i < n_recs_102; i++) {
        Entity_102 tempRect;
        tempRect.setup(min_side_length_102, max_side_length_102,
                       min_line_width_102, max_line_width_102,
                       min_n_lines_102, max_n_lines_102);
        rects_102.push_back(tempRect);
    }

}

//--------------------------------------------------------------
void ofApp::update_102(){
    // Update all rects, including the background rect
    background_rect_102.update();
    
    for(int i = 0; i < n_recs_102; i++) {
      rects_102[i].update();
    }
}

//--------------------------------------------------------------
void ofApp::draw_102(ofEventArgs & args){
    // Set blending mode off and draw a black background
    ofDisableBlendMode();
    ofBackground(backgroundColour_102);
    
    // Draw all rects, including the background rect
    background_rect_102.draw();
    
    for(int i = 0; i < n_recs_102; i++) {
      rects_102[i].draw();
    }
    
    // Draw some bit strings on screen for testing
    string info = "102 fps: " + ofToString(ofGetFrameRate(),2);
    ofDisableBlendMode();
    ofSetColor(255, 255, 255);
    ofDrawBitmapString(info, 10, 20);
    
}

void ofApp::clear_setup_102() {
    rects_102.clear();
    setup_102();
}

//--------------------------------------------------------------
//--------------------------------------------------------------
// ARDUINO STUFF
void ofApp::digitalPinChanged(const int & pinNum) {
    if (pinNum == ARD_PIN_101) {
        count_101 += 1;
        clear_setup_101();
        cout << "count 101: " << count_101 << endl;
    } else if (pinNum == ARD_PIN_102) {
        count_102 += 1;
        clear_setup_102();
        cout << "count 102: " << count_102 << endl;
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
    ard.sendDigitalPinMode(ARD_PIN_101, ARD_INPUT_PULLUP); // for 101
    ard.sendDigitalPinMode(ARD_PIN_102, ARD_INPUT_PULLUP); // for 102

    ofAddListener(ard.EDigitalPinChanged, this, &ofApp::digitalPinChanged);
}
//--------------------------------------------------------------
//--------------------------------------------------------------
