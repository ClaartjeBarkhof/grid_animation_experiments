#ifndef rect_h
#define rect_h
#include "ofMain.h"

class Entity_102 {

    public:
        // GENERAL METHODS
        void setup(int min_side_length, int max_side_length,
                   int min_line_width, int max_line_width,
                   int min_n_lines, int max_n_lines);
    
        void update();
        void draw();
    
        // What blend modes are available and which one is activated for this entity
        vector<ofBlendMode> blend_modes;
        int blend_mode_i;
    
        int n_lines;
    
        float cx, cy;
    
        ofColor color_rect, color_lines;
        float width, height;
        float scaled_width, scaled_height;
        
        bool horizontal;
    
        float where_scale;
        float where_lines;
    
        float scale;
        float translate_line;
    
        vector<float> line_widths, line_positions;

        Entity_102();
    
    private:
};


#endif /* rect_h */
