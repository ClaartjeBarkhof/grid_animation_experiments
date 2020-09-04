//
//  smallGrid.cpp
//  gridSketch_101
//
//  Created by Claartje Barkhof on 17/08/2020.
//

#include "smallGrid.hpp"

smallGrid::smallGrid(){
}

void smallGrid::setup(int _i, int _n_cols, float _width, float _height, int max_ent){
    i = _i;
    
    row = (int) i / _n_cols;
    col = (int) i % _n_cols;
    
    color.set(ofRandom(80), ofRandom(80),ofRandom(80));
    
    width = _width;
    height = _height;
    
    posX = (float)col * width;
    posY = (float)row * height;
    
    n_ent = ofRandom(max_ent);
}

void smallGrid::draw(){
    ofSetColor(color);
    ofFill();
    ofDrawRectangle(posX, posY, width, height);
}
