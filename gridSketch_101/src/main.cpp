#include "ofMain.h"
#include "ofApp_101.h"

//========================================================================
int main( ){
    
	ofSetupOpenGL(560, 580, OF_WINDOW);			// <-------- setup the GL context

    // this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp_101());

}
