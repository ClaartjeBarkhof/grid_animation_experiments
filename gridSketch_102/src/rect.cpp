//
//  rect.cpp
//  gridSketch_102
//
//  Created by Claartje Barkhof on 19/08/2020.
//

#include <stdio.h>
#include "rect.h"
#include "ofApp.h"
#include "ofMain.h"

Entity::Entity() {
}

void Entity::setup(int min_side_length, int max_side_length,
                   int min_line_width, int max_line_width,
                   int min_n_lines, int max_n_lines) {
    
    // Set width and height of the rect entitiy
    width = ofRandom(min_side_length, max_side_length);
    height = ofRandom(min_side_length, max_side_length);
    
    // Available blend modes
    blend_modes = {OF_BLENDMODE_DISABLED, OF_BLENDMODE_SUBTRACT,
    OF_BLENDMODE_MULTIPLY, OF_BLENDMODE_ALPHA,
    OF_BLENDMODE_SCREEN, OF_BLENDMODE_ADD};
    
//    blend_modes = {OF_BLENDMODE_DISABLED};
    
    // Which blend mode is activated for this rect entity
    blend_mode_i = (int)ofRandom(blend_modes.size()+1);
    
    n_lines = (int)ofRandom(min_n_lines, max_n_lines);
    
    // Colors of the rectangle and the lines in it are assigned randomly
    color_rect = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
    color_lines = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
    
    // Where to begin in terms of scale and line positions
    where_scale = ofRandom(TWO_PI);
    where_lines = ofRandom(TWO_PI);
    
    // Whether the rectangle is horizontally or vertically oriented
    if (ofRandom(1.0) > 0.5) {
        horizontal = true;
    } else {
        horizontal = false;
    }
    
//    cx = ofGetWidth() / 2.0;
//    cy = ofGetHeight() / 2.0;
    
    // Determine line widths and initial position
    for(int i = 0; i < n_lines; i++) {
        float line_p;
        if (horizontal == true) {
            line_p = ofRandom(-height, height);
        } else {
            line_p = ofRandom(-width, width);
        }
        float line_w = ofRandom(min_line_width, max_line_width);
        
        line_positions.push_back(line_p);
        line_widths.push_back(line_w);
    }
    
}

void Entity::update() {
    where_scale = where_scale + 0.01;
    scale = sin(where_scale) + 1.5; // to make sure it does not go all the way to 0
    
    where_lines = where_lines + 0.01;
    translate_line = sin(where_lines); // sin goes from -1 * 1
    
    scaled_width = (width * scale);
    scaled_height = (height * scale);
}

void Entity::draw() {
    // left upper corner of the rectangle
    float x = (ofGetWidth() / 2.0) - (scaled_width / 2.0);
    float y = (ofGetHeight() / 2.0) - (scaled_height / 2.0);
    
    ofEnableBlendMode(blend_modes[blend_mode_i]);
    ofSetColor(color_rect);
    
    ofDrawRectangle(x, y, scaled_width, scaled_height);
    
    for(int i = 0; i < n_lines; i++) {
        ofSetColor(color_lines);
      
      if (horizontal) {
          float y_line = y + (line_positions[i]*scale)+(translate_line*scaled_height);
          float subtract = (y_line + line_widths[i]*scale) - scaled_height;
    
          if (subtract > 0.0) {
              subtract = 0.0;
          }
          
          if ((y_line > y) && (y_line < (y + scaled_height)))  {
              ofDrawRectangle(x, y_line,scaled_width, line_widths[i]*scale-subtract);
          }
      
      } else {
          float x_line = x + (line_positions[i]*scale) + (translate_line*scaled_width);
          float subtract = (x_line + line_widths[i]*scale) - scaled_width;
            
          if (subtract > 0.0) {
              subtract = 0.0;
          }
          if ((x_line > x) && (x_line < (x + scaled_width))) {
              ofDrawRectangle(x_line, y, (line_widths[i]*scale) - subtract, scaled_height);
          }
      }
    }
}
