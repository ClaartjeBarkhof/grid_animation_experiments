#ifndef _LAYER
#define _LAYER
#include "ofMain.h" 

class Layer {

    public:

    void setup(int bpm);
    void update(bool gotonset);
    void draw(bool gotbeat);

    Layer();  
    private:
        bool start_drawing;
        vector<vector<float>> myRects;
        ofColor layerColor;
};
#endif
