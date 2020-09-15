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
        
        void draw_VIS();
        void update_VIS();
        void setup_VIS();

        void keyPressed(int key);
    
        void setup_GUI_SOUND();
        void draw_GUI_SOUND(ofEventArgs & args);
        void update_GUI_SOUND();
        void audioIn(float * input, int bufferSize, int nChannels);
        void audioOut(float * output, int bufferSize, int nChannel);
        void plot(vector<float>& buffer, float scale, float offset);    
        void onsetEvent(float & time);
        void beatEvent(float & time);

    private:
        // PITCH
        ofxAubioPitch pitch;
        ofxPanel pitchGui;
        ofxFloatSlider midiPitch;
        ofxFloatSlider pitchConfidence;

        // BEAT GUI
        ofxAubioBeat beat;
        ofxPanel beatGui;
        bool gotBeat;
        bool drawnBeatGUI, drawnBeatVIS;
        ofxFloatSlider bpm;

        // ONSET
        ofxAubioOnset onset;
        ofxPanel onsetGui;
        bool gotOnset;
        bool drawnOnsetGUI, drawnOnsetVIS;
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
    
        // SOUND STREAM
        ofSoundStream soundStream, outputStream;
        vector<float> samplesLeft;
        vector<float> samplesRight;
    
        // Visualisation stuff
        vector<Layer> allLayers;
        ofxPanel visGui;
        ofxButton addLayerButton;
        ofxButton deleteAllLayersButton;
        
        ofxButton selectLayerType1;
        ofxButton selectLayerType2;
        ofxButton selectLayerType3;
        
        ofParameter<bool> filled;
        
        void addLayerButtonPressed();
        void deleteAllLayersButtonPressed();
        void selectLayerType1Pressed();
        void selectLayerType2Pressed();
        void selectLayerType3Pressed();
        ofParameter<int> nCols;
        ofParameter<int> nRows;
        int layerType;
};
