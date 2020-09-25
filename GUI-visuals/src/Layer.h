#ifndef _LAYER
#define _LAYER
#include "ofMain.h" 


class Layer {

    public:

    void setup(int layerType_, int nCol_s, int nRows_, int signal_type,
               bool BlendModeOn, bool Subtract, bool Black);
    void update(bool signal);
    void draw();
    void draw_1();
    void draw_2();
    void draw_3();
    void draw_4();
    void update_1(bool signal);
    void update_2(bool signal);
    void update_3(bool signal);
    void update_4(bool signal);
    void die();
    void setup_layer_2();
    void setup_layer_4();
    void drawSubtracted(float x, float y, float w, float h, float w_s, float h_s);
    
    // GENERAL / HELPERS
    vector<ofBlendMode> blend_modes;
    
    // ALL / MULTIPLE LAYER TYPES
    ofColor layerColor;
    int layerType;
    int nCols, nRows;
    int signalType; // 0 for onset, 1 for beat
    ofBlendMode blendMode;
    float padding_perc;
    bool dying;
    bool ready_for_delete;
    
    // LAYER TYPE 1
    float disappear_start_time_1;
    bool disappear_1;
    float disappear_chance_1;
    vector<int> disappear_vec_1;
    
    // LAYER TYPE 2
    vector<vector<float>> myRects_2;
    float grow_scale_2;
    vector<float> getNewRect_2();
    
    // LAYER TYPE 3
    vector<vector<float>> myRects_3;
    
    // LAYER TYPE 4
    vector<float> positions_4;
    vector<float> lanes_4;
    bool vertical_4;
    int num_lanes_4;
    int current_lane_4;
    float length_4;

    Layer();  
    private:
        
};
#endif
