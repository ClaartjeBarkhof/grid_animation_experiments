#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){
    // Window for app 101
    ofGLFWWindowSettings settings;
    settings.setSize(600, 600);
    settings.setPosition(glm::vec2(600,0));
    settings.resizable = true;
    shared_ptr<ofAppBaseWindow> window_101 = ofCreateWindow(settings);

    // Window for app 102
    settings.setSize(600, 600);
    settings.setPosition(glm::vec2(0,0));
    settings.resizable = true;
    // uncomment next line to share main's OpenGL resources with gui
    //settings.shareContextWith = mainWindow;
    shared_ptr<ofAppBaseWindow> window_102 = ofCreateWindow(settings);
    window_102->setVerticalSync(false);

    shared_ptr<ofApp> mainApp(new ofApp);
    // Set-up and draw 102 too
    mainApp->setup_102();
    ofAddListener(window_102->events().draw, mainApp.get(), &ofApp::draw_102);

    ofRunApp(window_101, mainApp);
    ofRunMainLoop();
}
