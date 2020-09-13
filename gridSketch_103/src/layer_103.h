#ifndef layer_103_h
#define layer_103_h

#include "ofMain.h"

class Layer_103 {

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
        int layer_i;
        
        Layer_103();
    
    private:
};


#endif
