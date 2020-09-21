#include "Layer.h"

Layer::Layer(){
}

void Layer::setup(int layerType_, int nCols_, int nRows_, int signal_type, bool blendModeOn, bool subtract) {
    cout << "SETUP LAYER TYPE: " << layerType_ << " nCols: " << nCols_ << " nRows: " << nRows_ << endl;

    blend_modes = {OF_BLENDMODE_SUBTRACT, OF_BLENDMODE_MULTIPLY, OF_BLENDMODE_ALPHA, OF_BLENDMODE_SCREEN, OF_BLENDMODE_ADD};
    
    signalType = signal_type; // 0 for onset, 1 for beat
    layerType = layerType_;
    nCols = nCols_;
    nRows = nRows_;
    disappear_1 = false;
    
    if (blendModeOn) {
        blendMode = blend_modes[(int)ofRandom(blend_modes.size())];
    } else {
        blendMode = OF_BLENDMODE_DISABLED;
    }
    
    if (subtract) {
        blendMode = OF_BLENDMODE_SUBTRACT;
        layerColor = ofColor(255, 255, 255);
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
    
}

void Layer::update(bool signal) {
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
    float disappear_chance = 0.2;
    
    if ((signal) && !(disappear_1)) {
        disappear_1 = true;
        disappear_start_time_1 = ofGetElapsedTimef();
        for(int i = 0; i<(nRows*nCols); i++) {
            if (ofRandom(1.0) < disappear_chance) {
                disappear_vec_1.push_back(i);
            }
        }
    }
    
    if ((ofGetElapsedTimef() - disappear_start_time_1) > disappear_time_s) {
        disappear_1 = false;
        disappear_vec_1.clear();
    }
    
    
}

void Layer::draw_1() {
    
    
    float padding_w = ofGetWidth() * padding_perc;
    float padding_h = ofGetHeight() * padding_perc;
    
    ofFill();
    ofSetLineWidth(0);
    ofSetColor(layerColor);
    ofEnableBlendMode(blendMode);
    
    int i = 0;
    for(int r = 0; r<nRows; r++) {
        for(int c = 0; c<nCols; c++) {
            // either not disappear at all, or disappear by chance
            if (!(find(disappear_vec_1.begin(), disappear_vec_1.end(), i) != disappear_vec_1.end())) {
                float w = ofGetWidth() / nCols;
                float h = ofGetHeight() / nRows;
                
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

void Layer::setup_layer_2() {
    grow_scale_2 = (0.5*sin(ofGetElapsedTimef()*0.5)) + 1;
    
    float step = ofRandom(20, 40);
    float range = 20;
    float min = 100;
    float dif = 10;
 
    int count = 0;
    while (true) {
        float small_w = ofRandom(min, min+range);
        float small_h = ofRandom(min, min+range);
        float large_w = ofRandom(min+range+dif, min+(range*2)+dif);
        float large_h = ofRandom(min+range+dif, min+(range*2)+dif);
        
        if ((large_w > ofGetWidth()) || (large_h > ofGetHeight())) {
            break;
        }

        vector<float> rect = {large_w, large_h, small_w, small_h};
        myRects_2.push_back(rect);
        
        float large_side;
        if (large_w > large_h) {
            large_side = large_w;
        } else {
            large_side = large_h;
        }
        
        min = large_side + step;
        range *= 2;
        dif *= 2;
        count += 1;
    }
}

void Layer::update_2(bool signal) {
    grow_scale_2 = (0.5*sin(ofGetElapsedTimef())) + 1;
}

void Layer::draw_2() {
    float w_col = ofGetWidth() / nCols;
    float h_row = ofGetHeight() / nRows;
    
    for(int r = 0; r<nRows; r++) {
            for(int c = 0; c<nCols; c++) {
                for(int i = 0; i<myRects_2.size(); i++) {
                    
                    
                    float w_frac = (myRects_2[i][0] * grow_scale_2) / ofGetWidth();
                    float h_frac = (myRects_2[i][1] * grow_scale_2) / ofGetHeight();
                    float w_s_frac = (myRects_2[i][2] * grow_scale_2) / ofGetWidth();
                    float h_s_frac = (myRects_2[i][3] * grow_scale_2) / ofGetHeight();
                    
                    
                    float x = (ofGetWidth() / 2) - ((myRects_2[i][0] * grow_scale_2)/2.);
                    float y = (ofGetHeight() / 2) - ((myRects_2[i][1] * grow_scale_2)/2.);
                    
                    // Check what percentage the width of the rect is
                    float x_frac = x / ofGetWidth();
                    float y_frac = y / ofGetHeight();
                    
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
    if (signal) {
        vector<float> rect = {0., 0., (float)ofGetWidth(), (float)ofGetHeight()};
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
        myRects_3[i][0] = (ofGetWidth() / 2.)  - (myRects_3[i][2] / 2.);
        myRects_3[i][1] = (ofGetHeight() / 2.) - (myRects_3[i][3] / 2.);
    }
    
    // Erase rectangles that became too small
    sort(erase_rects.begin(), erase_rects.end(), greater<int>());
    for(int i = 0; i<erase_rects.size(); i++) {
        myRects_3.erase(myRects_3.begin() + erase_rects[i]);
    }
}

void Layer::draw_3() {
    float w_col = ofGetWidth() / nCols;
    float h_row = ofGetHeight() / nRows;
    
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
                float x_frac = myRects_3[i][0] / ofGetWidth();
                float y_frac = myRects_3[i][1] / ofGetHeight();
                float w_frac = myRects_3[i][2] / ofGetWidth();
                float h_frac = myRects_3[i][3] / ofGetHeight();
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
        cout << "HORIZONTAL" << endl;
        vertical_4 = false;
    }
    
    if (vertical_4) {
        length_4 = ofRandom(100, ofGetHeight()/2.);
    } else {
        length_4 = ofRandom(100, ofGetWidth()/2.);
    }
    
    num_lanes_4 = (int)ofRandom(20,40);
    current_lane_4 = 0;
}

void Layer::update_4(bool signal) {
    vector<int> erase_vec;
    
    if (signal) {
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
            if(positions_4[i] > ofGetHeight() + length_4) {
                erase_vec.push_back(i);
            }
        } else {
            if(positions_4[i] > ofGetWidth() + length_4) {
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
    
    

}

void Layer::draw_4() {
    ofFill();
    ofSetLineWidth(0);
    ofSetColor(layerColor);
    ofEnableBlendMode(blendMode);
    
    float relevant_side;
    if (vertical_4) {
        relevant_side = ofGetHeight();
    } else {
        relevant_side = ofGetWidth();
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
