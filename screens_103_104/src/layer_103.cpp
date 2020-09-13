#include "layer_103.h"

Layer_103::Layer_103() {
}

void Layer_103::setup(int i) {
    rows = (int)ofRandom(1, 5);
    cols = (int)ofRandom(1, 5);
    
    layer_i = i;
    
    padding = ofRandom(20, 40);
    
    if (ofRandom(1.0) < 0.25) {
        rectColor = ofColor(ofRandom(256), ofRandom(256), ofRandom(256));
        lineColor = ofColor(ofRandom(50), ofRandom(50), ofRandom(50));
        backgColor = ofColor(ofRandom(256), ofRandom(256), ofRandom(256));
    } else {
        rectColor = ofColor(ofRandom(256), ofRandom(256), ofRandom(256));
        lineColor = ofColor(ofRandom(256), ofRandom(256), ofRandom(256));
        backgColor = ofColor(ofRandom(256), ofRandom(256), ofRandom(256));
    }
        
    nLines = (int)ofRandom(5, 20);
    lineWidth = ofRandom(10, 20);
    position = ofRandom(0, 1);
    
    // Available blend modes
    blend_modes = {OF_BLENDMODE_SUBTRACT, OF_BLENDMODE_MULTIPLY, OF_BLENDMODE_ALPHA, OF_BLENDMODE_SCREEN, OF_BLENDMODE_ADD}; //OF_BLENDMODE_DISABLED, 
    
    if (layer_i == 0) {
        // First layer no blendmode
        blend_mode_i = 0;
        
    } else {
        // Which blend mode is activated for this rect entity
        blend_mode_i = (int)ofRandom(0, blend_modes.size());
    }
        
//    cout << "Blendmode: " << blend_mode_i << endl;
    
}

void Layer_103::update() {
    position -= 0.02;
    if (position <= 0.0) {
        position = 1.0;
    }
}

void Layer_103::draw() {
    if (blend_mode_i == 0) {
//        cout << "DISABLE" << endl;
        ofDisableBlendMode();
    } else {
        ofEnableBlendMode(blend_modes[blend_mode_i]);
    }
    
    if (layer_i == 0) {
        ofSetColor(backgColor);
        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    }
    
    float wRect = (ofGetWidth()  - ((cols + 1) * padding)) / cols;
    float hRect = (ofGetHeight() - ((rows + 1) * padding)) / rows;
    
    vector<float> widths;
    float totalWidth = 0;
    for (int l = 0; l<nLines; l++) {
        float whereScale = ((float)(l)/(float)nLines) * TWO_PI;
        float scale = 1.0 * sin(whereScale) + 1.2;
        float scaledWidth = lineWidth; //* scale;
        totalWidth += scaledWidth;
        widths.push_back(scaledWidth);
    }
    
    // Negative space between the lines
    float negWidth = ((wRect+widths[0]) - totalWidth) / nLines;
    
    for(int r = 0; r<rows; r++) {
        for(int c = 0; c<cols; c++) {
            ofSetColor(rectColor);
            float xRect = (c+1)*padding + (c*wRect);
            float yRect = (r+1)*padding + (r*hRect);
            ofDrawRectangle(xRect, yRect, wRect, hRect);
            
            ofSetColor(lineColor);
            for (int l = 0; l<nLines+1; l++) {
                float offset = (position * (negWidth+widths[l])) - widths[l];
                float widthsSoFar = accumulate(widths.begin(), widths.begin()+l, 0);
                float xLine = xRect + widthsSoFar + (l * negWidth) + offset;
                
                float xDraw = xLine;
                float yDraw = yRect;
                float wDraw = widths[l];
                float hDraw = hRect;
                
                float whereScale = ((xDraw-xRect) / wRect) * TWO_PI;
                float scale = 1.0 * sin(whereScale) + 1.2;
                wDraw *= scale;
                
                if (xDraw <= xRect) {
                    wDraw -= (xRect - xDraw);
                    xDraw = xRect;
                }
                
                if ((xDraw + wDraw) >= (xRect + wRect)) {
                    wDraw -= ((xDraw + wDraw) - (xRect + wRect));
                }
                
                if (wDraw > 0) {
                    ofDrawRectangle(xDraw, yDraw, wDraw, hDraw);
                }
            }
        }
    }
    ofDisableBlendMode();
}
