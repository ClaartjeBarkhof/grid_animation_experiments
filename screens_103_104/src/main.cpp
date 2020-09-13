#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){
    // Window for app 103
    ofGLFWWindowSettings settings;
    settings.setSize(600, 600);
    settings.setPosition(glm::vec2(600,0));
    settings.resizable = true;
    shared_ptr<ofAppBaseWindow> window_103 = ofCreateWindow(settings);

    // Window for app 102
    settings.setSize(600, 600);
    settings.setPosition(glm::vec2(0,0));
    settings.resizable = true;
    // uncomment next line to share main's OpenGL resources with gui
    //settings.shareContextWith = mainWindow;
    shared_ptr<ofAppBaseWindow> window_104 = ofCreateWindow(settings);
    window_104->setVerticalSync(false);

    shared_ptr<ofApp> mainApp(new ofApp);
    // Set-up and draw 102 too
    mainApp->setup_104();
    ofAddListener(window_104->events().draw, mainApp.get(), &ofApp::draw_104);

    ofRunApp(window_103, mainApp);
    ofRunMainLoop();
}
