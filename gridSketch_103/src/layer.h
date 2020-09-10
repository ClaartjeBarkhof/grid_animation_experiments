#ifndef layer_h
#define layer_h

#include "ofMain.h"

class Layer {

    public:
        // GENERAL METHODS
        int rows, cols;
        float padding;
        void setup(int i);
        void update();
        void draw();
    
        ofColor rectColor, lineColor, backgColor;
        int nLines;
    
        float position;
        float lineWidth;
    
        vector<ofBlendMode> blend_modes;
        int blend_mode_i;
        
        Layer();
    
    private:
};


#endif
