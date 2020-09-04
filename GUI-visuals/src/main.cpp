#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    // WIDTH, HEIGHT
	ofSetupOpenGL(750, 1000, OF_FULLSCREEN); // otherwise OF_WINDOW

	ofRunApp(new ofApp());
}
