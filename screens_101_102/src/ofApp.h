#pragma once

#include "ofMain.h"
#include "rect_102.h"
#include "entity_101.h"

class ofApp : public ofBaseApp{

	public:
        void setup();
        void update();
        void draw();
    
        //--------------------------------------------
        // 101 FUNCTIONS
        void setup_101();
        void update_101();
        void draw_101();
        void clear_setup_101();
        int getCell_101(int row, int col, int n_cols);
        
        //--------------------------------------------
        // 102 FUNCTIONS
        void setup_102();
        void update_102();
        void draw_102(ofEventArgs & args);
        void clear_setup_102();
    
    //--------------------------------------------
    // 101 ATTRIBUTES
    vector<ofColor> background_colors_101;
    vector<vector<int>> entity_per_cell_101;
    vector <Entity_101> allEntities_101;

    int n_cols_101;
    int n_rows_101;
    float width_cell_101, height_cell_101;
    int min_ent_cell_101, max_ent_cell_101;
    
    //--------------------------------------------
    // 102 ATTRIBUTES
    int min_n_lines_102;
    int max_n_lines_102;
    int min_side_length_102; // min width in scale 1.0, it scales to x 2.4
    int max_side_length_102;
    int min_line_width_102;
    int max_line_width_102;
    int min_n_recs_102;
    int max_n_recs_102;

    ofColor backgroundColour_102;
    int n_recs_102;

    vector<Entity_102> rects_102;
    Entity_102 background_rect_102;
		
    //--------------------------------------------
    // ARDUINO STUFF
    ofArduino   ard;
    bool        bSetupArduino;
    
    void setupArduino(const int & version); //
    void digitalPinChanged(const int & pinNum);
    
    int count_101;
    int count_102;
};
