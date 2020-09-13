#pragma once

#include "ofMain.h"
#include "entity_104.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
        void setup_104();
        void update_104();
        void draw_104();
        void clear_setup_104();

		void keyPressed(int key);
    
    vector<Entity_104> allEntities_104;
    int nEntities_104;
		
};
