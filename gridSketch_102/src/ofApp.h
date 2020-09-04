#pragma once

#include "ofMain.h"
#include "rect.h"

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

        vector<Entity> rects;
        Entity background_rect;
		
};
