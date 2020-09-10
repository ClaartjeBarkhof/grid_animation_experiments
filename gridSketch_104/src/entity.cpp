//
//  entity.cpp
//  gridSketch_104
//
//  Created by Claartje Barkhof on 09/09/2020.
//

#include <stdio.h>
#include "entity.h"

Entity::Entity() {
}

void Entity::setup(float percPosRef, bool vertical_, bool first, bool firstOfAll) {
    
    // BLENDMODE + COLORS
    blendModes = {OF_BLENDMODE_DISABLED, OF_BLENDMODE_SUBTRACT, OF_BLENDMODE_MULTIPLY, OF_BLENDMODE_ADD, OF_BLENDMODE_ALPHA, OF_BLENDMODE_SCREEN};
        
    whichBlendMode = (int)ofRandom(1, blendModes.size());
    if (firstOfAll) {
        whichBlendMode = 0;
    }

    cout << "whichBlendMode: " << whichBlendMode << endl;
    
    fgColor = ofColor(ofRandom(256), ofRandom(256), ofRandom(256));
    
    nLines = (int)ofRandom(2, 12);
    
    nStripes = (int)ofRandom(5, 25);
    float maxWidthStripe;
    if (vertical) {
        maxWidthStripe = ofGetHeight() / (float)nStripes - 5;
    } else {
        maxWidthStripe = ofGetWidth() / (float)nStripes - 5;
    }
    widthStripe = ofRandom(5, maxWidthStripe);
    
    vertical = vertical_;
    if (firstOfAll) {
        if (vertical) {
            widthLine = ofGetWidth() / (float)nLines;
        } else {
            widthLine = ofGetHeight() / (float)nLines;
        }
        
    } else {
        
        widthLine = ofRandom(20, 200);
        
    }
    

    
    // If second, make black and blending mode off
    if (!first) {
        fgColor = ofColor(0, 0, 0);
        whichBlendMode = 0;
    }
    
    float max_speed = 0.05;
    float min_speed = 0.01;
    
//    float minHeight = 600;
//    float minWidth = 600;
    
//    float probabilityFullScreen = 1.0;
    
    // Define a bounding box for the entity to live in
//    if (ofRandom(1) < probabilityFullScreen) {
//        minX = 0.0;
//        maxX = ofGetWidth();
//        minY = 0.0;
//        maxY = ofGetHeight();
//    } else {
//        minX = ofRandom(-minWidth, ofGetWidth());
//        minY = ofRandom(-minHeight, ofGetHeight());
//
//        maxX = ofRandom(minX+minWidth, ofGetWidth()-minWidth);
//        maxY = ofRandom(minY+minHeight, ofGetHeight()-minHeight);
//    }
    minX = 0.0;
    maxX = ofGetWidth();
    minY = 0.0;
    maxY = ofGetHeight();
    
    cout << "minX: " << minX << endl;
    cout << "minY: " << minY << endl;
    cout << "maxX: " << maxX << endl;
    cout << "maxY: " << maxY << endl;
    cout << "ofGetWidth: " << ofGetWidth() << endl;
    cout << "ofGetHeight: " << ofGetHeight() << endl;
    
    widthEnt = maxX - minX;
    heightEnt = maxY - minY;
    
    cout << "nLines: " << nLines << endl;
    cout << "nStripes: " << nStripes << endl;
    cout << "widthLine: " << widthLine << endl;
    cout << "widthStripe: " << widthStripe << endl;
    
    if (vertical) {
        posRef = minX + percPosRef * widthEnt;
        negSpace = (heightEnt-(nStripes*widthStripe)) / nStripes;
    } else {
        posRef = minY + percPosRef * heightEnt;
        negSpace = (widthEnt-(nStripes*widthStripe)) / nStripes;
    }
    
    for(int i = 0; i<nLines; i++) {
        float p = ofRandom(1);
        offSetStripes.push_back(p);
        
        if (ofRandom(1) < 0.5) {
            leftMovingLines.push_back(true);
        } else {
            leftMovingLines.push_back(false);
        }
        
        speedLines.push_back(ofRandom(min_speed, min_speed));
    }
    
}

void Entity::update() {
    
    for(int i = 0; i<nLines; i++) {
        if (leftMovingLines[i]) {
            offSetStripes[i] -= speedLines[i];
            if (offSetStripes[i] < 0.0) {
                offSetStripes[i] = 1.0;
            }
        } else {
            offSetStripes[i] += speedLines[i];
            if (offSetStripes[i] > 1.0) {
                offSetStripes[i] = 0.0;
            }
        }
    }
    
}

void Entity::draw() {
    
//    ofSetColor(ofColor(ofRandom(256), ofRandom(256), ofRandom(256)));
//    ofSetColor(ofColor::yellow);
//    ofDrawRectangle(minX, minY, widthEnt, heightEnt);
    
    ofEnableBlendMode(blendModes[whichBlendMode]);
//    ofSetColor(bgColor);
    
//    if (bgColorTrue) {
//        if (vertical) {
//            ofDrawRectangle(posRef, minY, nLines*widthLine, heightEnt);
//        } else {
//            ofDrawRectangle(minX, posRef, widthEnt, nLines*widthLine);
//        }
//    }
    
    for(int i = 0; i<nLines; i++) {
        ofSetColor(fgColor);
        for(int j = 0; j<nStripes+1; j++) {
            float offsetStripe = j*(negSpace+widthStripe);
            float offsetFirstStripe = offSetStripes[i]*(negSpace+widthStripe)-widthStripe;
            if (vertical) {
                float x = posRef+(i*widthLine);
                float y = minY + offsetFirstStripe+offsetStripe;
                float hDraw = widthStripe;
                
                if ((y+widthStripe) > maxY) {
                    hDraw -= ((y+widthStripe) - maxY);
                }
                
                if (y < minY) {
                    float dif = minY - y;
                    hDraw -= dif;
                    y += dif;
                }
                
                if (hDraw > 0) {
                    ofDrawRectangle(x, y, widthLine, hDraw);
                }
                
            } else {
                float y = posRef+(i*widthLine);
                float x = minX + offsetFirstStripe+offsetStripe;
                
                float wDraw = widthStripe;
                if ((x+widthStripe) > maxX) {
                    wDraw -= ((x+widthStripe) - maxX);
                }
                
                if (x < minX) {
                    float dif = minX - x;
                    wDraw -= dif;
                    x += dif;
                }
                
                if (wDraw > 0) {
                    ofDrawRectangle(x, y, wDraw, widthLine);
                }
                
                
            }
        }
    }
    ofDisableBlendMode();
    
}
