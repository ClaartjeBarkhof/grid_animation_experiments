//
//  entity.cpp
//  gridSketch_101
//
//  Created by Claartje Barkhof on 17/08/2020.
//

#include <stdio.h>
#include "entity.h"
#include "ofMain.h"
#include "ofApp.h"

Entity::Entity(){
}

void Entity::setup(int _cell_i, int _n_rows, int _n_cols){
    // GLOBALS
    options = { {0, 0, 4, 5}, {1, 0, 2, 5}, {1, 1, 2, 5}, {1, 1, 2, 4},
    {0, 1, 3, 4}, {1, 1, 3, 4}, {1, 0, 3, 6}, {0, 0, 3, 6},
    {0, 0, 3, 1}, {0, 5, 3, 1}, {0, 5, 1, 1}, {0, 0, 1, 1},
    {0, 1, 3, 5}, {0, 1, 4, 5}, {1, 0, 3, 1}, {1, 5, 3, 1},
    {3, 0, 1, 1}, {3, 5, 1, 1}, {0, 5, 4, 1}, {0, 0, 4, 1}};
    
    blend_modes = { OF_BLENDMODE_DISABLED, OF_BLENDMODE_SUBTRACT,
                    OF_BLENDMODE_MULTIPLY, OF_BLENDMODE_ALPHA,
                    OF_BLENDMODE_SCREEN, OF_BLENDMODE_ADD}; 
    
    blend_mode_i = (int)ofRandom(blend_modes.size());
        
    MAX_grow_factor = 2;
    
    n_cols = _n_cols;
    n_rows = _n_rows;

    n_cols_small = 4;
    n_rows_small = 6;
    
//    cell_x_random_w = (int)ofRandom(1, 4);
//    cell_x_random_h = (int)ofRandom(1, 3);
    
    cell_x_random_w = 1;
    cell_x_random_h = 1;
    
//    cout << "cell_x_random_w: " << cell_x_random_w << endl;
//    cout << "cell_x_random_h: " << cell_x_random_h << endl;
//
    width_cell = ofGetWidth() / n_cols;
    height_cell = ofGetHeight() / n_rows;
    
//    cout << "width_cell: " << width_cell << endl;
//    cout << "height_cell: " << height_cell << endl;
//
    cell_i = _cell_i;
    
    where = - (1/2) * PI;
    where_change_scale = - (1/2) * PI;
    
    color.set(ofRandom(255),ofRandom(255),ofRandom(255));
    
    how_from = options[(int)ofRandom(options.size())];
    how_to = options[(int)ofRandom(options.size())];
    
    change_scale_from = (int)ofRandom(1, MAX_grow_factor+1);
    change_scale_to = (int)ofRandom(1, MAX_grow_factor+1);

}

void Entity::update(){
    change_scale = sin(where);
    grow_shrink_scale = sin(where_change_scale);
    
//    change_scale = 1;
//    grow_shrink_scale = 1;

    int x_from = how_from[0];
    int y_from = how_from[1];
    int w_from = how_from[2];
    int h_from = how_from[3];
    
    int x_to = how_to[0];
    int y_to = how_to[1];
    int w_to = how_to[2];
    int h_to = how_to[3];
         
    posX = (float)x_from + (change_scale * (x_to - x_from));
    posY = (float)y_from + (change_scale * (y_to - y_from));
    
    width_ent = ((float)w_from + (change_scale * (w_to - w_from))) * cell_x_random_w;
    height_ent = ((float)h_from + (change_scale * (h_to - h_from))) * cell_x_random_h;
    
    where = where + 0.01;
    where_change_scale = where_change_scale + 0.01;

    // if at the end of the transition initialise a new transition point
    if (where > (0.5 * PI)) {
      where = - (1/2) * PI;
      how_from = how_to;
      how_to = change(how_from);
    }
    
    if (where_change_scale > (0.5 * PI)) {
      where_change_scale = - (1/2) * PI;
      change_scale_from = change_scale_to;
      change_scale_to = (int)ofRandom(1, MAX_grow_factor+1);
    }
}

void Entity::draw(int scale){
    // If the cell is a grid of 4 x 6 what are the sizes of the sides of the grid cubes
    float SIDE_CUBE_w = width_cell / n_cols_small;
    float SIDE_CUBE_h = height_cell / n_rows_small;
    
    // Given an cell_i, what is the row and column of the cell
    int row = getRow(cell_i, n_cols);
    int col = getCol(cell_i, n_cols);
    
    // Get the left upper position of the cell (small_grid)
    float pos_x_small_grid = col * width_cell;
    float pos_y_small_grid = row * height_cell;
    
    // Get the absolute position of the entity in the screen
    float abs_pos_x = pos_x_small_grid + (posX * SIDE_CUBE_w);
    float abs_pos_y = pos_y_small_grid + (posY * SIDE_CUBE_h);
    
    ofSetColor(color);
    ofEnableBlendMode(blend_modes[blend_mode_i]);
    ofDrawRectangle(abs_pos_x, abs_pos_y,
                    width_ent * SIDE_CUBE_w * (float)scale,
                    height_ent * SIDE_CUBE_h * (float)scale);
    
}

int Entity::getRow(int i, int n_cols) {
    int row = (int)i / n_cols;
    return row;
}

int Entity::getCol(int i, int n_cols) {
    int col = (int)i % n_cols;
    return col;
}

int Entity::getCell(int row, int col, int n_cols) {
    int cell = (int)(row * n_cols) + col;
    return cell;
}

int Entity::giveRandomIndex(int n_options) {
  return (int)ofRandom(n_options);
}

vector<int> Entity::change(vector<int> input) {
    vector<int> dummy_output = {9, 9, 9, 9};
    
    vector<int> a = {0, 0, 4, 5};
    if (input == a) {
      int choice = giveRandomIndex(4);
      if (choice == 0) {
        vector<int> output = {1, 0, 2, 5};
        return output;
      } else if (choice == 1) {
        vector<int> output = {1, 1, 2, 5};
        return output;
      } else if (choice == 2) {
        vector<int> output = {0, 0, 4, 1};
        return output;
      } else {
        vector<int> output = {0, 1, 3, 5};
        return output;
      }
    }
    
    vector<int> b = {1, 0, 2, 5};
    if (input == b) {
      int choice = giveRandomIndex(2);
      if (choice == 0) {
        vector<int> output = {0, 0, 4, 5};
        return output;
      } else {
        vector<int> output = {1, 1, 2, 4};
        return output;
      }
    }
    
    vector<int> c = {1, 1, 2, 5};
    if (input == c) {
      int choice = giveRandomIndex(2);
      if (choice == 0) {
        vector<int> output = {0, 0, 4, 5};
        return output;
      } else {
        vector<int> output = {1, 1, 2, 4};
        return output;
      }
    }
    
    vector<int> d = {1, 1, 2, 4};
    if (input == d) {
      int choice = giveRandomIndex(4);
      if (choice == 0) {
        vector<int> output = {1, 0, 2, 5};
        return output;
      } else if (choice == 1) {
        vector<int> output = {1, 1, 2, 5};
        return output;
      } else if (choice == 1) {
        vector<int> output = {0, 1, 3, 4};
        return output;
      } else {
        vector<int> output = {1, 1, 3, 4};
        return output;
      }
    }
    
    vector<int> e = {0, 1, 3, 4};
    if (input == e) {
      int choice = giveRandomIndex(2);
      if (choice == 0) {
        vector<int> output = {0, 0, 3, 6};
        return output;
      } else {
        vector<int> output = {1, 1, 2, 4};
        return output;
      }
    }
    
    vector<int> f = {1, 1, 3, 4};
    if (input == f) {
      int choice = giveRandomIndex(2);
      if (choice == 0) {
        vector<int> output = {1, 0, 3, 6};
        return output;
      } else {
        vector<int> output = {1, 1, 2, 4};
        return output;
      }
    }
    
    vector<int> g = {1, 0, 3, 6};
    if (input == g) {
      int choice = giveRandomIndex(3);
      if (choice == 0) {
        vector<int> output = {1, 1, 3, 4};
        return output;
      } else if (choice == 1) {
        vector<int> output = {1, 0, 3, 1};
        return output;
      } else {
        vector<int> output = {1, 5, 3, 1};
        return output;
      }
    }
    
    vector<int> h = {0, 0, 3, 6};
    if (input == h) {
      int choice = giveRandomIndex(3);
      if (choice == 0) {
        vector<int> output = {0, 1, 3, 4};
        return output;
      } else if (choice == 1) {
        vector<int> output = {0, 0, 3, 1};
        return output;
      } else {
        vector<int> output = {0, 5, 3, 1};
        return output;
      }
    }
    
    vector<int> i = {0, 0, 3, 1};
    if (input == i) {
      int choice = giveRandomIndex(3);
      if (choice == 0) {
        vector<int> output = {0, 0, 1, 1};
        return output;
      } else if (choice == 1) {
        vector<int> output = {0, 0, 3, 6};
        return output;
      } else {
        vector<int> output = {0, 0, 4, 1};
        return output;
      }
    }
    
    vector<int> j = {0, 5, 3, 1};
    if (input == j) {
      int choice = giveRandomIndex(3);
      if (choice == 0) {
        vector<int> output = {0, 0, 3, 6};
        return output;
      } else if (choice == 1) {
        vector<int> output = {0, 5, 1, 1};
        return output;
      } else {
        vector<int> output = {0, 5, 4, 1};
        return output;
      }
    }
    
    vector<int> k = {0, 5, 1, 1};
    if (input == k) {
      int choice = giveRandomIndex(2);
      if (choice == 0) {
        vector<int> output = {0, 5, 3, 1};
        return output;
      } else {
        vector<int> output = {0, 5, 4, 1};
        return output;
      }
    }
    
    vector<int> l = {0, 0, 1, 1};
    if (input == l) {
      int choice = giveRandomIndex(2);
      if (choice == 0) {
        vector<int> output = {0, 0, 3, 1};
        return output;
      } else {
        vector<int> output = {0, 0, 4, 1};
        return output;
      }
    }
    
    vector<int> m = {0, 1, 3, 5};
    if (input == m) {
      int choice = giveRandomIndex(4);
      if (choice == 0) {
        vector<int> output = {0, 0, 4, 5};
        return output;
      } else if (choice == 1) {
        vector<int> output = {0, 1, 3, 4};
        return output;
      } else if (choice == 2) {
        vector<int> output = {1, 1, 3, 4};
        return output;
      } else {
        vector<int> output = {0, 1, 4, 5};
        return output;
      }
    }
    
    vector<int> n = {0, 1, 4, 5};
    if (input == n) {
      int choice = giveRandomIndex(2);
      if (choice == 0) {
        vector<int> output = {0, 1, 3, 5};
        return output;
      } else {
        vector<int> output = {0, 5, 4, 1};
        return output;
      }
    }
    
    vector<int> o = {1, 0, 3, 1};
    if (input == o) {
      int choice = giveRandomIndex(3);
      if (choice == 0) {
        vector<int> output = {1, 0, 3, 6};
        return output;
      } else if (choice == 1) {
        vector<int> output = {3, 0, 1, 1};
        return output;
      } else {
        vector<int> output = {0, 0, 4, 1};
        return output;
      }
    }
    
    vector<int> p = {1, 5, 3, 1};
    if (input == p) {
      int choice = giveRandomIndex(3);
      if (choice == 0) {
        vector<int> output = {1, 0, 3, 6};
        return output;
      } else if (choice == 1) {
        vector<int> output = {3, 5, 1, 1};
        return output;
      } else {
        vector<int> output = {0, 5, 4, 1};
        return output;
      }
    }
    
    vector<int> q = {3, 0, 1, 1};
    if (input == q) {
      int choice = giveRandomIndex(2);
      if (choice == 0) {
        vector<int> output = {1, 0, 3, 1};
        return output;
      } else {
        vector<int> output = {0, 0, 4, 1};
        return output;
      }
    }
    
    vector<int> r = {3, 5, 1, 1};
    if (input == r) {
      int choice = giveRandomIndex(2);
      if (choice == 0) {
        vector<int> output = {1, 5, 3, 1};
        return output;
      } else {
        vector<int> output = {0, 5, 4, 1};
        return output;
      }
    }
    
    vector<int> s = {0, 5, 4, 1};
    if (input == s) {
      int choice = giveRandomIndex(2);
      if (choice == 0) {
        vector<int> output = {1, 5, 3, 1};
        return output;
      } else {
        vector<int> output = {3, 5, 1, 1};
        return output;
      }
    }
    
    vector<int> t = {0, 0, 4, 1};
    if (input == t) {
      int choice = giveRandomIndex(2);
      if (choice == 0) {
        vector<int> output = {3, 0, 1, 1};
        return output;
      } else {
        vector<int> output = {1, 0, 3, 1};
        return output;
      }
    }
    
    // sanity check
    cout << "None matched!" << endl;
    return dummy_output;
}
