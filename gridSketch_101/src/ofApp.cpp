#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // GLOBALS
    max_ent_cell = (int)ofRandom(1, 5);
    min_ent_cell = (int)ofRandom(2);
    
    if (ofRandom(1.0) > 0.5) {
        n_cols = (int)ofRandom(1, 10);
        n_rows = (int)ofRandom(1, 4);
    } else {
        n_cols = (int)ofRandom(1, 4);
        n_rows = (int)ofRandom(1, 10);
    }
    
    frameRate = 60;
    
    ofSetFrameRate(frameRate);
    ofSetVerticalSync(false);
    
    int max_scale;
    
    if (ofRandom(1.0) > 0.5) {
        max_scale = 2;
    } else {
        max_scale = 1;
    }

    cout << "max_ent: " << max_ent_cell << " min_ent: " << min_ent_cell << endl;
    cout << "n_cols: " << n_cols << " n_rows: " << n_rows << endl;
    
    // Width of the cells or small grids
    width_cell = ofGetWidth() / n_cols;
    height_cell = ofGetHeight() / n_rows;
    
    for (int i = 0; i < n_rows * n_cols; i++) {
        // Random color of background of cells
        ofColor tempColor;
        tempColor.set(ofRandom(120),ofRandom(120),ofRandom(120));
        background_colors.push_back(tempColor);
        
        // Random scale (x1 or x2) for each cell or small grid
        scale_per_cell.push_back((int)ofRandom(1, max_scale+1));
    }
    
    // Keep track for that cell which entities (indices) belong to it
    int ent_counter = 0;
    entity_per_cell.resize(n_cols * n_rows);
    speed_per_cell.resize(n_cols * n_rows);
    
    // For every cell (row, col): add a random number of entities
    for (int r = 0; r < n_rows; r++){
        for(int c = 0; c < n_cols; c++) {

            // Row, col corresponds to cell i
            int cell_i = getCell(r, c, n_cols);
            
            // Number of entities in this cell
            int n_ents = (int)ofRandom(min_ent_cell, max_ent_cell);
            
            // Keep track for that cell which entities (indices) belong to it
            entity_per_cell[cell_i].resize(n_ents);
            speed_per_cell[cell_i] = ofRandom(1, 5);
            
            // Add the entities
            for (int n = 0; n <= n_ents; n++) {

                // Add the entity to the vector of entities
                Entity tempEnt;
                tempEnt.setup(cell_i, n_rows, n_cols);
                allEntities.push_back(tempEnt);
                
                // Keep track for that cell which entities (indices) belong to it
                entity_per_cell[cell_i].push_back(ent_counter);
                
                // Count the entities total
                ent_counter++;
            }
        }
    }
    
    
}


//--------------------------------------------------------------
void ofApp::update(){
    
    ofSetFrameRate(frameRate);
    
    for(int i = 0; i<allEntities.size(); i++) {
        allEntities[i].update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    
    // Iterate over cells (rows and colls)
    int cell_i = 0;
    for (int r = 0; r < n_rows; r++){
        for(int c = 0; c < n_cols; c++) {
            
            // Get the scale of the cell (x1 or x2)
            int scale = scale_per_cell[cell_i];
            
            if (scale == 1) {
                ofDisableBlendMode();
                
                // Draw background of cell
                ofSetColor(background_colors[cell_i]);
                ofDrawRectangle(c * width_cell, r * height_cell,
                                width_cell * (float)scale,
                                height_cell * (float)scale);
                
                // Draw entities in cell
                for(int n = 0; n < entity_per_cell[cell_i].size(); n++) {
                    allEntities[entity_per_cell[cell_i][n]].draw(scale);
                }
            }
            
            cell_i++;
        }
    }
    
    // Iterate over cells (rows and colls)
    cell_i = 0;
    for (int r = 0; r < n_rows; r++){
        for(int c = 0; c < n_cols; c++) {
            
            // Get the scale of the cell (x1 or x2)
            int scale = scale_per_cell[cell_i];
            
            if (scale == 2) {
                
                ofDisableBlendMode();
                
                // Draw background of cell
                ofSetColor(background_colors[cell_i]);
                ofDrawRectangle(c * width_cell, r * height_cell,
                                width_cell * (float)scale,
                                height_cell * (float)scale);
                
                // Draw entities in cell
                for(int n = 0; n < entity_per_cell[cell_i].size(); n++) {
                    allEntities[entity_per_cell[cell_i][n]].draw(scale);
                }
            }
            
            cell_i++;
        }
    }
    
    // Draw some bit strings on screen for testing
//    string info = "fps: " + ofToString(ofGetFrameRate(),2);
//    ofDisableBlendMode();
//    ofSetColor(255, 255, 255);
//    ofDrawBitmapString(info, 10, 20);
//    
//    ofDrawBitmapString("Press 'r' for random restart!" , 10, 60);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    // Press 'r' for restart!
    if(key == 'r') {
        // Delete data in vectors
        background_colors.clear();
        scale_per_cell.clear();
        entity_per_cell.clear();
        speed_per_cell.clear();
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

int ofApp::getRow(int i, int n_cols) {
    int row = (int)i / n_cols;
    return row;
}

int ofApp::getCol(int i, int n_cols) {
    int col = (int)i % n_cols;
    return col;
}

int ofApp::getCell(int row, int col, int n_cols) {
    int cell = (int)(row * n_cols) + col;
    return cell;
}
