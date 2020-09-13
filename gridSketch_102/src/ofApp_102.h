#pragma once

#include "ofMain.h"
#include "rect_102.h"

class ofApp_102 : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
    
        int min_n_lines;
        int max_n_lines;
        int min_side_length; // min width in scale 1.0, it scales to x 2.4
        int max_side_length;
        int min_line_width;
        int max_line_width;
        int min_n_recs;
        int max_n_recs;

        ofColor backgroundColour;
        int n_recs;

        vector<Entity_102> rects;
        Entity_102 background_rect;
		
};
