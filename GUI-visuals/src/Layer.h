#ifndef _LAYER
#define _LAYER
#include "ofMain.h" 

class Layer {

    public:

    void setup(int layerType_, int nCol_s, int nRows_);
    void update(bool signal);
    void draw();
    void draw_1();
    void draw_2();
    void draw_3();
    void update_1(bool signal);
    void update_2(bool signal);
    void update_3(bool signal);
    
    // GENERAL / HELPERS
    vector<ofBlendMode> blend_modes;
    
    // ALL LAYER TYPES
    ofColor layerColor;
    int layerType;
    int nCols, nRows;
    
    // LAYER TYPE 2
    vector<vector<float>> myRects_2;
    ofBlendMode blendMode_2;
    
    // LAYER TYPE 3
    vector<vector<float>> myRects_3;

    Layer();  
    private:
        
};
#endif
