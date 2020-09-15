#include "ofApp_101.h"

//--------------------------------------------------------------
void ofApp_101::setup(){
    setup_101();
}

//--------------------------------------------------------------
void ofApp_101::update(){
    update_101();
}

void ofApp_101::draw(){
    draw_101();
//    drawInfo();
}

void ofApp_101::update_101(){
    for(int i = 0; i<allEntities_101.size(); i++) {
        allEntities_101[i].update();
    }
}

void ofApp_101::setup_101() {
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

    cout << "max_ent: " << max_ent_cell_101 << " min_ent: " << min_ent_cell_101 << endl;
    cout << "n_cols_101: " << n_cols_101 << " n_rows_101: " << n_rows_101 << endl;
    
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
void ofApp_101::drawInfo(){
    // Draw some bit strings on screen for testing
    string info = "fps: " + ofToString(ofGetFrameRate(),2);
    ofDisableBlendMode();
    ofSetColor(255, 255, 255);
    ofDrawBitmapString(info, 10, 20);
    ofDrawBitmapString("Press 'r' for random restart!" , 10, 60);
}

//--------------------------------------------------------------
void ofApp_101::draw_101(){
    ofBackground(0);
    
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
}

void ofApp_101::clear_101() {
    // Delete data in vectors
    background_colors_101.clear();
    entity_per_cell_101.clear();
    allEntities_101.clear();
    
    setup();
}

//--------------------------------------------------------------
void ofApp_101::keyPressed(int key) {
    // Press 'r' for restart!
    if(key == 'r') {
        clear_101();
    }
}

int ofApp_101::getCell_101(int row, int col, int n_cols) {
    int cell = (int)(row * n_cols) + col;
    return cell;
}
