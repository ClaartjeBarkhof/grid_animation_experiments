//
//  smallGrid.hpp
//  gridSketch_101
//
//  Created by Claartje Barkhof on 17/08/2020.
//

#ifndef smallGrid_hpp
#define smallGrid_hpp

#include <stdio.h>
#include "ofMain.h"

class smallGrid {

    public: // place public functions or variables declarations here

    // methods, equivalent to specific functions of your class objects
    void setup(int _i, int _n_cols, float _width, float _height, int max_ent);
    void draw();    // draw method, this where you'll do the object's drawing

    // variables
    int i;
    int row;
    int col;
    
    int n_ent;
    
    float posX;
    float posY;
    
    float width;
    float height;
    
    ofColor color;  // color using ofColor type

    smallGrid();  // constructor - used to initialize an object
    
    private:
};

#endif /* smallGrid_hpp */
