#pragma once

#include "ofMain.h"
#include "layer_103.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
        void setup_103();
		void update();
        void update_103();
		void draw();
        void draw_103();
        void clear_setup_103();

		void keyPressed(int key);
        
    vector<Layer_103> allLayers1_103, allLayers2_103, allLayers3_103, allLayers4_103;
    int nLayers1_103, nLayers2_103, nLayers3_103, nLayers4_103;
    
    ofFbo fbo1_103, fbo2_103, fbo3_103, fbo4_103;
    
    ofColor bgColor_103;
};
