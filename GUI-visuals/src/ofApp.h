#pragma once

#include "ofMain.h"
#include "ofxAubio.h"
#include "ofxGui.h"
#include "ofxFft.h"
#include "Layer.h"

class ofApp : public ofBaseApp{

    public:
        void setup();
        void exit();

        void update();
        void draw();
        void draw_visuals();
    
        void plot(vector<float>& buffer, float scale, float offset);

        void keyPressed(int key);
        void keyReleased(int key);
        void mouseMoved(int x, int y );
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
        void windowResized(int w, int h);
        void dragEvent(ofDragInfo dragInfo);
        void gotMessage(ofMessage msg);

        void audioIn(float * input, int bufferSize, int nChannels);
        void audioOut();

        void onsetEvent(float & time);
        void beatEvent(float & time);

    private:
        // AUBIO
        

        // PITCH
        ofxAubioPitch pitch;
        ofxPanel pitchGui;
        ofxFloatSlider midiPitch;
        ofxFloatSlider pitchConfidence;

        // BEAT GUI
        ofxAubioBeat beat;
        ofxPanel beatGui;
        bool gotBeat;
        ofxFloatSlider bpm;

        // ONSET
        ofxAubioOnset onset;
        ofxPanel onsetGui;
        bool gotOnset;
        ofxFloatSlider onsetThreshold;
        ofxFloatSlider onsetNovelty;
        ofxFloatSlider onsetThresholdedNovelty;

        // BANDS
        ofxAubioMelBands bands;
        ofxPanel bandsGui;
        ofPolyline bandPlot;
    
        int plotHeight, bufferSize;
    
        // FAST FOURIER TRANSFORMS
        ofxFft* fft;
            
        // SPECTROGRAM
        ofImage spectrogram; // matrix with drawn frequency arrays, one column gets updated every time
        int spectrogramOffset; // x coordinate of where we are right now
                
        // For sharing data between sound and main (update, draw, etc.) thread
        ofMutex soundMutex;
    
        // BINS & BUFFER
        vector<float> drawBins, middleBins, audioBins;
        vector<float> drawBuffer, middleBuffer, audioBuffer;
    
        // Visualisation stuff
        vector<Layer> allLayers;
        ofxPanel visGui;
        ofxButton addLayerButton;
        void addLayerButtonPressed();
};
