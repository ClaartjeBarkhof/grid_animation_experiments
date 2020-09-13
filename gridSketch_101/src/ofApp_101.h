#pragma once

#include "ofMain.h"
#include "entity_101.h"

class ofApp_101 : public ofBaseApp{

	public:
		void setup();
		void update();
        void draw();
    
		void keyPressed(int key);
    
        // GENERAL HELPER FUNC.
        void drawInfo();
        
        //------------------------------------------
        // FUNCTIONS FOR 101
        void draw_101();
        
        void clear_101();
        void setup_101();
        void update_101();
        int getCell_101(int row, int col, int n_cols);
        //------------------------------------------

    //------------------------------------------
    // ATTRIBUTES FOR 101
    vector<ofColor> background_colors_101;
    vector<vector<int>> entity_per_cell_101;
    vector <Entity_101> allEntities_101;

    int n_cols_101;
    int n_rows_101;
    float width_cell_101, height_cell_101;
    int min_ent_cell_101, max_ent_cell_101;
    //------------------------------------------
};
