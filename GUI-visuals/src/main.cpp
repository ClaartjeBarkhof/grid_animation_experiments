#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){
    // Window for visuals
    ofGLFWWindowSettings settings;
    settings.setSize(600, 600);
    settings.setPosition(glm::vec2(800,0));
    settings.resizable = true;
    shared_ptr<ofAppBaseWindow> window_VIS = ofCreateWindow(settings);
    
    // Window for GUI and plots
    settings.setSize(800, 900);
    settings.setPosition(glm::vec2(0,0));
    settings.resizable = true;
    
    // uncomment next line to share main's OpenGL resources with gui
    //settings.shareContextWith = mainWindow;
    shared_ptr<ofAppBaseWindow> window_GUI_SOUND = ofCreateWindow(settings);
    window_GUI_SOUND->setVerticalSync(false);

    shared_ptr<ofApp> mainApp(new ofApp);
    // Set-up and draw 102 too
    mainApp->setup_GUI_SOUND();
    ofAddListener(window_GUI_SOUND->events().draw, mainApp.get(), &ofApp::draw_GUI_SOUND);

    ofRunApp(window_VIS, mainApp);
    ofRunMainLoop();
}
