#pragma once

#include "ofMain.h"
#include "layer.h"

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
    
        void setup_layers(vector<Layer>);
    
    vector<Layer> allLayers1, allLayers2, allLayers3, allLayers4;
    int nLayers1, nLayers2, nLayers3, nLayers4;
    
    ofFbo fbo1, fbo2, fbo3, fbo4;
    
    float balance;
    
    
		
};
