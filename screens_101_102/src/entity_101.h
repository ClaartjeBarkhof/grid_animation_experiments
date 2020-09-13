#ifndef entity_h
#define entity_h

#include "ofMain.h"

class Entity_101 {

    public:
        // GENERAL METHODS
        void setup(int _cell_i, int _n_rows, int _n_cols);
        void update();
        void draw();
    
        // HELPER FUNCTIONS
        int getCell(int row, int col, int n_cols);
        int getRow(int i, int n_cols);
        int getCol(int i, int n_cols);
        int giveRandomIndex(int n_options);
        
        // FUNCTION WITH GRID RULES
        vector<int> change(vector<int> input);
    
        vector<ofBlendMode> blend_modes;
        int blend_mode_i;
        
        // GLOBALS
        // All the positions and sizes for rects stored in a 2D vector
        vector<vector<int>> options;
        int MAX_grow_factor, n_cols, n_rows, n_cols_small, n_rows_small;
        float width_cell, height_cell;
        int cell_x_random_w, cell_x_random_h;
        
        // ATTRIBUTES OF ENTITY
        int cell_i;
        ofColor color;
        float width_ent, height_ent;
        float change_scale, grow_shrink_scale;
        float posX, posY;
        vector<int> how_to, how_from; // transition definition
        float where, where_change_scale, change_scale_from, change_scale_to;

        Entity_101();
    
    private:
};
#endif
