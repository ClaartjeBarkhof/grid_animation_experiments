#pragma once

#include "ofMain.h"
#include "ofxAubio.h"
#include "ofxBeat.h"
#include "ofxGui.h"
#include "ofxFft.h"
#include "Layer.h"

enum {MIC_SPEAKER, SOUNDCARD_SPEAKER};

class ofApp : public ofBaseApp{

    public:
        void setup();
        void exit();

        void update();
        void draw();
        
        void draw_VIS();
        void drawLayerTypeX(int X);
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
    
        // ofxbeat
        ofxBeat beat_ofx;

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
        // For passing 2 channel sound directly to speakers
        vector<float> samplesLeft;
        vector<float> samplesRight;
        
        int mode; // MIC_SPEAKER, SOUNDCARD_SPEAKER
    
        // Visualisation stuff
        vector<Layer> allLayers;
        ofxPanel visGui;
        ofxButton addLayerButton;
        ofxButton addLayerFrontButton;
        ofxButton deleteAllLayersButton;
    
        ofxButton deleteFirstButton;
        ofxButton deleteLastButton;
        
        ofParameter<bool> LayerType1;
        ofParameter<bool> LayerType2;
        ofParameter<bool> LayerType3;
        ofParameter<bool> LayerType4;
        ofParameter<bool> onsetSignalType;
        ofParameter<bool> beatSignalType;
        ofParameter<bool> beatSnareSignalType;
        ofParameter<bool> beatKickSignalType;
        ofParameter<bool> beatHihatSignalType;
        ofParameter<bool> blendModeOn;
        ofParameter<bool> Subtract;
        ofParameter<bool> Black;
    
        int signalType;
        int layerType;
        
        void addLayerButtonPressed();
        void addLayerFrontButtonPressed();
        void deleteAllLayersButtonPressed();
        void handleSelectedParams();
        void deleteLastButtonPressed();
        void deleteFirstButtonPressed();
        ofParameter<int> nCols;
        ofParameter<int> nRows;
        
};
