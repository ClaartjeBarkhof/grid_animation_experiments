#include "Layer.h"

Layer::Layer(){
}

void Layer::setup(int layerType_, int nCols_, int nRows_, int signal_type,
                  bool blendModeOn, bool subtract, bool Black, float widthScreen_, float heightScreen_) {
    cout << "SETUP LAYER TYPE: " << layerType_ << " nCols: " << nCols_ << " nRows: " << nRows_ << endl;

    blend_modes = {OF_BLENDMODE_SUBTRACT, OF_BLENDMODE_MULTIPLY, OF_BLENDMODE_ALPHA, OF_BLENDMODE_SCREEN, OF_BLENDMODE_ADD};
    
    signalType = signal_type; // 0 for onset, 1 for beat
    layerType = layerType_;
    nCols = nCols_;
    nRows = nRows_;
    disappear_1 = false;
    dying = false;
    ready_for_delete = false;
    disappear_chance_1 = 0.2;
    
    widthScreen = widthScreen_;
    heightScreen = heightScreen_;
    
    if (blendModeOn) {
        blendMode = blend_modes[(int)ofRandom(blend_modes.size())];
    } else {
        blendMode = OF_BLENDMODE_DISABLED;
    }

    padding_perc = ofRandom(0.01, 0.05);
    
    if (layerType == 2) {
        setup_layer_2();
        layerColor = ofColor(ofRandom(150), ofRandom(150), ofRandom(150));
    } else {
        layerColor = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
    }
    
    if (layerType == 4) {
        setup_layer_4();
    }
    
    if (subtract) {
        blendMode = OF_BLENDMODE_SUBTRACT;
        layerColor = ofColor(255, 255, 255);
    }
    
    if (Black) {
        blendMode = OF_BLENDMODE_DISABLED;
        layerColor = ofColor(0, 0, 0);
    }
    
}

void Layer::update(bool signal, float widthScreen_, float heightScreen_) {
    widthScreen = widthScreen_;
    heightScreen = heightScreen_;
    
    if (layerType == 1) {
        update_1(signal);
    }
    if (layerType == 2) {
        update_2(signal);
    }
    if (layerType == 3) {
        update_3(signal);
    }
    if (layerType == 4) {
        update_4(signal);
    }
}

void Layer::draw(){
    if (layerType == 1) {
        draw_1();
    }
    if (layerType == 2) {
        draw_2();
    }
    if (layerType == 3) {
        draw_3();
    }
    if (layerType == 4) {
        draw_4();
    }
}

void Layer::update_1(bool signal) {
    float disappear_time_s = 0.2;
    
    
    if ((signal) && !(disappear_1)) {
        disappear_1 = true;
        disappear_start_time_1 = ofGetElapsedTimef();
        for(int i = 0; i<(nRows*nCols); i++) {
            if ((nCols == 1) && (nRows == 1)) {
                disappear_vec_1.push_back(i);
            }
            else if (ofRandom(1.0) < disappear_chance_1) {
                disappear_vec_1.push_back(i);
            }
        }
    }
    
    if ((ofGetElapsedTimef() - disappear_start_time_1) > disappear_time_s) {
        disappear_1 = false;
        disappear_vec_1.clear();
    }
    
    // Let more and more disappear
    if (dying) {
//        cout << "disappear_chance_1: " << disappear_chance_1 << endl;
        disappear_chance_1 += 0.01;
        if (disappear_chance_1 >= 1.0) {
            ready_for_delete = true;
        }
    }
    
    
}

void Layer::draw_1() {
    
    
    float padding_w = widthScreen * padding_perc;
    float padding_h = heightScreen * padding_perc;
    
    ofFill();
    ofSetLineWidth(0);
    ofSetColor(layerColor);
    ofEnableBlendMode(blendMode);
    
    int i = 0;
    for(int r = 0; r<nRows; r++) {
        for(int c = 0; c<nCols; c++) {
            // either not disappear at all, or disappear by chance
            if (!(find(disappear_vec_1.begin(), disappear_vec_1.end(), i) != disappear_vec_1.end())) {
                float w = widthScreen / nCols;
                float h = heightScreen / nRows;
                
                float p_w = padding_perc * w;
                float p_h = padding_perc * h;
                
                w -= (p_w*2);
                h -= (p_h*2);
                
                float x = p_w + (c * w) + (2*p_w*c);
                float y = p_h + (r * h) + (2*p_h*r);
                            
                ofDrawRectangle(x, y, w, h);
            }
            i += 1;
        }
    }
}

void Layer::die() {
    dying = true;
}

vector<float> Layer::getNewRect_2() {
    float range = 20;
    float min = 100;
    float dif = 10;
    
    float small_w = ofRandom(min, min+range);
    float small_h = ofRandom(min, min+range);
    float large_w = ofRandom(min+range+dif, min+(range*2)+dif);
    float large_h = ofRandom(min+range+dif, min+(range*2)+dif);
    
    vector<float> rect{large_w, large_h, small_w, small_h};
    return rect;
}

void Layer::setup_layer_2( ) {
    myRects_2.push_back(getNewRect_2());
}

void Layer::update_2(bool signal) {
    // Grow a bit every update (exponentially
    for(int i = 0; i<myRects_2.size(); i++) {
        myRects_2[i][0] *= 1.01;
        myRects_2[i][1] *= 1.01;
        myRects_2[i][2] *= 1.01;
        myRects_2[i][3] *= 1.01;
    }
    
    if (myRects_2.size() > 0) {
        // If last added rect is bigger than init rec, add another
        if ((myRects_2.back()[2] > 200) && (myRects_2.back()[2] > 200) && (signal) && (!dying)) {
//            cout << "IF 1" << endl;
            myRects_2.push_back(getNewRect_2());
        }
    }
    
    
    if ((myRects_2.size() == 0) && (signal) && (!dying)) {
//        cout << "IF 2" << endl;
        myRects_2.push_back(getNewRect_2());
    }
    
    
    // Record which rectangles to erase
    vector<int> erase_rects;
    
    // If last added rect is bigger than screen, remove it
    for(int i = 0; i<myRects_2.size(); i++) {
        if ((myRects_2.back()[2] >= widthScreen) && (myRects_2.back()[3] >= heightScreen)) {
            erase_rects.push_back(i);
        }
    }
    
    // Erase rectangles that became too small
    sort(erase_rects.begin(), erase_rects.end(), greater<int>());
    for(int i = 0; i<erase_rects.size(); i++) {
        myRects_2.erase(myRects_2.begin() + erase_rects[i]);
    }
    
    // If dying and no rects are left, delete the layer
    if ((dying) && (myRects_2.size() == 0)) {
        ready_for_delete = true;
    }
    
//    cout << "size myrects 2: " << myRects_2.size() << endl;
}

void Layer::draw_2() {
    float w_col = widthScreen / nCols;
    float h_row = heightScreen / nRows;

    for(int r = 0; r<nRows; r++) {
            for(int c = 0; c<nCols; c++) {
                for(int i = 0; i<myRects_2.size(); i++) {
                    // large_w, large_h, small_w, small_h
                    float l_w = myRects_2[i][0];
                    float l_h = myRects_2[i][1];
                    float s_w = myRects_2[i][2];
                    float s_h = myRects_2[i][3];
                    
                    if (l_w > widthScreen) {
                        l_w = widthScreen;
                    }
                    
                    if (l_h > heightScreen) {
                        l_h = heightScreen;
                    }
                    
                    if (s_w > widthScreen) {
                        s_w = widthScreen;
                    }
                    
                    if (s_h > heightScreen) {
                        s_h = heightScreen;
                    }
                    
                    float w_frac = l_w / widthScreen;
                    float h_frac = l_h / heightScreen;
                    float w_s_frac = s_w / widthScreen;
                    float h_s_frac = s_h / heightScreen;
                    
                    float x = (widthScreen / 2) - (l_w/2.);
                    float y = (heightScreen / 2) - (l_h/2.);
                    
                    // Check what percentage the width of the rect is
                    float x_frac = x / widthScreen;
                    float y_frac = y / heightScreen;
                    
                    x = (c*w_col) + (x_frac*w_col);
                    y = (r*h_row) + (y_frac*h_row);
                    float w = w_col * w_frac;
                    float h = h_row * h_frac;
                    float w_s = w_col * w_s_frac;
                    float h_s = h_row * h_s_frac;
                    
                    drawSubtracted(x, y, w, h, w_s, h_s);
                }
            }
        }
}

void Layer::drawSubtracted(float x, float y, float w, float h, float w_s, float h_s) {
    ofEnableBlendMode(blendMode);
    
    float x_s = x+(w/2)-(w_s/2);
    float y_s = y+(h/2)-(h_s/2);
    
    ofPath path;
    path.setFillColor(layerColor);

    path.moveTo(x,y);
    path.lineTo(x+w,y);
    path.lineTo(x+w,y+h);
    path.lineTo(x,y+h);
    path.close();

    path.moveTo(x_s,y_s);
    path.lineTo(x_s+w_s,y_s);
    path.lineTo(x_s+w_s,y_s+h_s);
    path.lineTo(x_s,y_s+h_s);
    path.close();

    path.draw();
    ofDisableBlendMode();
}

void Layer::update_3(bool signal) {
    float min_rect_size = 100.;
    float shrink_scale = 0.98;
    
    // If new onset, new rect
    if ((signal) && (!dying)) {
        vector<float> rect = {0., 0., widthScreen, heightScreen};
        myRects_3.push_back(rect);
    }
    
    // Record which rectangles to erase
    vector<int> erase_rects;
    
    // Shrink the rects over time, erase when size ~ 0
    for(int i = 0; i<myRects_3.size(); i++) {
        // Check size if smaller than thresh, store their index for removal
        if ((myRects_3[i][2] < min_rect_size) || (myRects_3[i][3] < min_rect_size)) {
            erase_rects.push_back(i);
        }

        // Scale with and height
        myRects_3[i][2] *= shrink_scale;
        myRects_3[i][3] *= shrink_scale;

        // Calculate x, y upperleft
        myRects_3[i][0] = (widthScreen / 2.)  - (myRects_3[i][2] / 2.);
        myRects_3[i][1] = (heightScreen / 2.) - (myRects_3[i][3] / 2.);
    }
    
    // Erase rectangles that became too small
    sort(erase_rects.begin(), erase_rects.end(), greater<int>());
    for(int i = 0; i<erase_rects.size(); i++) {
        myRects_3.erase(myRects_3.begin() + erase_rects[i]);
    }
    
    // If dying and no rects are left, delete the layer
    if ((dying) && (myRects_3.size() == 0)) {
        ready_for_delete = true;
    }
}

void Layer::draw_3() {
    float w_col = widthScreen / nCols;
    float h_row = heightScreen / nRows;
    
    // No fill and red color
    ofNoFill();
    ofSetColor(layerColor);
    ofEnableBlendMode(blendMode);
    
    for(int r = 0; r<nRows; r++) {
        for(int c = 0; c<nCols; c++) {
            for(int i = 0; i<myRects_3.size(); i++) {
                // Check what percentage the width of the rect is
//                float p =  myRects_3[i][2] / ofGetWidth();
                ofSetLineWidth(1);
                float x_frac = myRects_3[i][0] / widthScreen;
                float y_frac = myRects_3[i][1] / heightScreen;
                float w_frac = myRects_3[i][2] / widthScreen;
                float h_frac = myRects_3[i][3] / heightScreen
                ;
                float x = (c*w_col) + (x_frac*w_col);
                float y = (r*h_row) + (y_frac*h_row);
                float w = w_col * w_frac;
                float h = h_row * h_frac;
                ofDrawRectangle(x, y, w, h);
            }
        }
    }
    ofDisableBlendMode();
    
}

void Layer::setup_layer_4() {
    if (ofRandom(1.0) < 0.5) {
        vertical_4 = true;
    } else {
        vertical_4 = false;
    }
    
    if (vertical_4) {
        length_4 = ofRandom(100, heightScreen/2.);
    } else {
        length_4 = ofRandom(100, widthScreen/2.);
    }
    
    num_lanes_4 = (int)ofRandom(20,40);
    current_lane_4 = 0;
}

void Layer::update_4(bool signal) {
    vector<int> erase_vec;
    
    if ((signal) && (!dying)) {
        int lane = (int)ofRandom(num_lanes_4);
        positions_4.push_back(-length_4/2);
        lanes_4.push_back(lane);
        current_lane_4 += 1;
        if (current_lane_4 > num_lanes_4) {
            current_lane_4 = 0;
        }
    }
    
    for(int i = 0; i<positions_4.size(); i++) {
        positions_4[i] += 10;
        
        if(vertical_4) {
            if(positions_4[i] > heightScreen + length_4) {
                erase_vec.push_back(i);
            }
        } else {
            if(positions_4[i] > widthScreen + length_4) {
                erase_vec.push_back(i);
            }
        }
    }
    
    // Erase rectangles that are outside the screen
    sort(erase_vec.begin(), erase_vec.end(), greater<int>());
    for(int i = 0; i<erase_vec.size(); i++) {
        positions_4.erase(positions_4.begin() + erase_vec[i]);
        lanes_4.erase(lanes_4.begin() + erase_vec[i]);
    }
    
    
    // If dying and no rects are left, delete the layer
    if ((dying) && (positions_4.size() == 0)) {
        ready_for_delete = true;
    }
}

void Layer::draw_4() {
    ofFill();
    ofSetLineWidth(0);
    ofSetColor(layerColor);
    ofEnableBlendMode(blendMode);
    
    float relevant_side;
    if (vertical_4) {
        relevant_side = heightScreen;
    } else {
        relevant_side = widthScreen;
    }
    
    float side = relevant_side / num_lanes_4;
    float p = side * padding_perc;
    
    for(int i = 0; i<positions_4.size(); i++) {
        if (vertical_4) {
            float x = lanes_4[i]*side + p + (2*p*lanes_4[i]);
            float y = positions_4[i];
            ofDrawRectangle(x, y, side, length_4);
        } else {
            float y = lanes_4[i]*side + p + (2*p*lanes_4[i]);
            float x = positions_4[i];
            ofDrawRectangle(x, y, length_4, side);
        }
    }
            

}
