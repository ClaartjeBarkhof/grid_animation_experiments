#ifndef layer_h
#define layer_h

#include "ofMain.h"

class Layer {

    public:
        // GENERAL METHODS
        int rows, cols;
        float padding;
        void setup();
        void update();
        void draw();
    
        ofColor rectColor, lineColor;
        int nLines;
    
        float position;
        float lineWidth;
        
        Layer();
    
    private:
};


#endif
