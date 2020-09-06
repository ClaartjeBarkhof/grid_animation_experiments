#include "layer.h"

Layer::Layer() {
}

void Layer::setup() {
    rows = (int)ofRandom(1, 5);
    cols = (int)ofRandom(1, 5);
    
    padding = ofRandom(20, 40);
    rectColor = ofColor(ofRandom(256), ofRandom(256), ofRandom(256));
    lineColor = ofColor(ofRandom(256), ofRandom(256), ofRandom(256));
    
    nLines = (int)ofRandom(5, 20);
    lineWidth = ofRandom(10, 20);
    position = ofRandom(0, 1);
}

void Layer::update() {
    position -= 0.01;
    if (position <= 0.0) {
        position = 1.0;
    }
}

void Layer::draw() {
    ofBackground(200, 30, 100);
    
    //
    float wRect = (ofGetWidth()  - ((cols + 1) * padding)) / cols;
    float hRect = (ofGetHeight() - ((rows + 1) * padding)) / rows;
    
    
    
    // Negative space between the lines
    float negWidth = ((wRect+lineWidth) - (nLines * lineWidth)) / nLines;
    
    for(int r = 0; r<rows; r++) {
        for(int c = 0; c<cols; c++) {
//            ofSetColor(rectColor);
            ofSetColor(ofColor::red);
            float xRect = (c+1)*padding + (c*wRect);
            float yRect = (r+1)*padding + (r*hRect);
            ofDrawRectangle(xRect, yRect, wRect, hRect);
            
            ofSetColor(ofColor::blue);
            
            vector<float> widths;
            float total_width = 0;
            for(int l = 0; l<nLines; l++) {
                float where_scale = ((l+1)/nLines) * position;
                float scale = 1.0 * sin(where_scale) + 1.2;
                float scaledWidth = lineWidth * scale;
                total_width += scaledWidth;
                widths.push_back(scaledWidth);
            }
            
            for(int l = 0; l<nLines; l++) {
                float offset = (position * (negWidth+lineWidth)) - lineWidth;
                float xLine = xRect + (l * (lineWidth + negWidth)) + offset;
                
                float xDraw = xLine;
                float yDraw = yRect;
                float wDraw = lineWidth;
                float hDraw = hRect;
                
                float where_scale = ((xRect + (l * (lineWidth + negWidth))) / wRect) * TWO_PI;
                float scale =
                wDraw *= scale;
                
                if (xDraw <= xRect) {
                    wDraw -= (xRect - xDraw);
                    xDraw = xRect;
                }
                
                if ((xDraw + wDraw) >= (xRect + wRect)) {
                    wDraw -= ((xDraw + wDraw) - (xRect + wRect));
                }

                ofDrawRectangle(xDraw, yDraw, wDraw, hDraw);
                
                
            }
            
        }
    }
}
