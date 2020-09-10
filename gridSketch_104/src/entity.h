//
//  entity.h
//  gridSketch_104
//
//  Created by Claartje Barkhof on 09/09/2020.
//

#ifndef entity_h
#define entity_h

#include "ofMain.h"

class Entity {

    public:
        // GENERAL METHODS
        void setup(float percPosRef, bool vertical_, bool first, bool firstOfAll);
        void update();
        void draw();
    
        // Blend Mode & color
        vector<ofBlendMode> blendModes;
        int whichBlendMode;
        ofColor bgColor, fgColor;
        bool bgColorTrue;
    
        bool vertical;
        int nLines;
        int nStripes;
        float widthLine, widthStripe;
        float posRef;
        float negSpace;
        float percPosFirstStripe, percOffsetOtherStripes;
        float absPosFirstStripe, absOffsetOtherStripes;
    
        vector<float> offSetStripes;
        vector<bool> leftMovingLines;
        vector<float> speedLines;
    
        float minX, maxX, minY, maxY;
        float widthEnt, heightEnt;
  
        Entity();
    
    private:
};

#endif /* entity_h */
