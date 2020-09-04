#pragma once

#include "ofMain.h"
#include "entity.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        int getCell(int row, int col, int n_cols);
        int getRow(int i, int n_cols);
        int getCol(int i, int n_cols);
        
        void drawBG();
    
    vector<ofColor> background_colors;
    
    vector<int> scale_per_cell;
    vector<vector<int>> entity_per_cell;
    
    vector<float> speed_per_cell;
    vector <Entity> allEntities;
    
    
    int frameRate;
    
    int n_cols;
    int n_rows;
    float width_cell, height_cell;
    
    int min_ent_cell, max_ent_cell;
    
    
		
};
