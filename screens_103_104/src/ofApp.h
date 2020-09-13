#pragma once

#include "ofMain.h"
#include "layer_103.h"
#include "entity_104.h"

class ofApp : public ofBaseApp{

	public:
        void setup();
        void update();
        void draw();
        void keyPressed(int key);
    
        //--------------------------------------------
        // 103 FUNCTIONS
        void setup_103();
        void update_103();
        void draw_103();
        void clear_setup_103();
        
        //--------------------------------------------
        // 104 FUNCTIONS
        void setup_104();
        void update_104();
        void draw_104(ofEventArgs & args);
        void clear_setup_104();
    
    //--------------------------------------------
    // 103 ATTRIBUTES
    vector<Layer_103> allLayers1_103, allLayers2_103, allLayers3_103, allLayers4_103;
    int nLayers1_103, nLayers2_103, nLayers3_103, nLayers4_103;
    ofFbo fbo1_103, fbo2_103, fbo3_103, fbo4_103;
    ofColor bgColor_103;
    
    //--------------------------------------------
    // 104 ATTRIBUTES
    vector<Entity_104> allEntities_104;
    int nEntities_104;
    
    //--------------------------------------------
    // ARDUINO STUFF
    ofArduino   ard;
    bool        bSetupArduino;
    
    void setupArduino(const int & version); //
    void digitalPinChanged(const int & pinNum);
    
    int count_103;
    int count_104;
		
};
