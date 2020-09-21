#include "ofApp.h"
#include "ofEventUtils.h"

int MIC_IN = 0;
int SOUND_FLOWER_IN_OUT = 2;

//--------------------------------------------------------------
//--------------------------------------------------------------
// MAIN LOOP FUNCTIONS
//--------------------------------------------------------------
void ofApp::setup(){
    mode = MIC_SPEAKER; // available modes MIC_SPEAKER, SOUNDCARD_SPEAKER
    setup_VIS();
    setup_GUI_SOUND();
    
    // To handle the onset & beat signals
    // (don't remove the signals before having
    // drawn them in GUI as well as visuals) --> see update() for logic
    gotBeat = false;
    gotOnset = false;
    drawnOnsetVIS = false;
    drawnOnsetGUI = false;
    drawnBeatVIS = false;
    drawnBeatGUI = false;
}

void ofApp::update(){
    update_VIS();
    update_GUI_SOUND();
    
    beat_ofx.update(ofGetElapsedTimeMillis());
    
    handleSelectedParams();
    if ((gotOnset) && (drawnOnsetVIS) && (drawnOnsetGUI)) {
        gotOnset = false;
    }
    if ((gotBeat) && (drawnBeatVIS) && (drawnBeatGUI)) {
        gotBeat = false;
    }
}

// This only calls draw VIS because draw GUI is triggered by events by drawing
void ofApp::draw(){
    draw_VIS();
}

//--------------------------------------------------------------
//--------------------------------------------------------------
// HELPER & EXTRA FUNCTIONS
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // TO BE IMPLEMENTED
}

float powFreq(float i) {
    // Floating point power to the third
    return powf(i, 3);
}


//--------------------------------------------------------------
//--------------------------------------------------------------
// VISUALS
//--------------------------------------------------------------
void ofApp::update_VIS(){
//    cout << "VIS UPDATE" << endl;
    
    for(int i = 0; i < allLayers.size(); i++) {
        if (allLayers[i].signalType == 0) {
            allLayers[i].update(gotOnset);
        } else {
            allLayers[i].update(gotBeat);
        }
    }
}

void ofApp::drawLayerTypeX(int X) {
    for(int i = 0; i < allLayers.size(); i++) {
        if (allLayers[i].layerType == X) {
            allLayers[i].draw();
        }
    }
}

void ofApp::draw_VIS() {
//    cout << "VIS DRAW" << endl;
    ofBackground(0, 0, 0);
    
    ofSetColor(ofColor::blue);
    ofFill();
    
//    drawLayerTypeX(1);
//    drawLayerTypeX(2);
//    drawLayerTypeX(3);
    
    for(int i = 0; i < allLayers.size(); i++) {
        allLayers[i].draw();
    }
    
    if (gotOnset) {
        drawnOnsetVIS = true;
    }
    if (gotBeat) {
        drawnBeatVIS = true;
    }
}

void ofApp::setup_VIS(){
//    cout << "VIS SET-UP" << endl;
}

//--------------------------------------------------------------
//--------------------------------------------------------------
// GUI - VIS INTERACTION
//--------------------------------------------------------------
void ofApp::addLayerButtonPressed(){
    Layer newLayer;
    newLayer.setup(layerType, nCols, nRows, signalType, blendModeOn, Subtract); // 0 for onset, 1 for beat
    allLayers.push_back(newLayer);
}

void ofApp::addLayerFrontButtonPressed(){
    Layer newLayer;
    newLayer.setup(layerType, nCols, nRows, signalType, blendModeOn, Subtract); // 0 for onset, 1 for beat
    allLayers.insert(allLayers.begin(), newLayer);
}

void ofApp::deleteAllLayersButtonPressed() {
    allLayers.clear();
}

void ofApp::deleteFirstButtonPressed() {
    if (allLayers.size() > 0) {
        allLayers.erase(allLayers.begin());
    }
}

void ofApp::deleteLastButtonPressed() {
    if (allLayers.size() > 0) {
        allLayers.pop_back();
    }
}

//--------------------------------------------------------------
//--------------------------------------------------------------
// GUI & SOUND
//-------------------------------------------------------------
void ofApp::setup_GUI_SOUND() {
    //    cout << "GUI SOUND SET-UP" << endl;
    // GLOBALS & SETTINGS
    plotHeight = 128;
    bufferSize = 512;
    ofSetVerticalSync(true);

    // FAST FOURIER TRANSFORM
    fft = ofxFft::create(bufferSize, OF_FFT_WINDOW_HAMMING);

    // SPECTROGRAM: MATRIX (ofImage) BUFFERSIZE X N_BINS
    spectrogram.allocate(bufferSize, fft->getBinSize(), OF_IMAGE_GRAYSCALE);
    spectrogram.setColor(ofColor::black);

    // TIME DOMAIN BUFFER
    drawBuffer.resize(bufferSize);
    middleBuffer.resize(bufferSize);
    audioBuffer.resize(bufferSize);

    // FREQ DOMAIN BINS
    drawBins.resize(fft->getBinSize());
    middleBins.resize(fft->getBinSize());
    audioBins.resize(fft->getBinSize());

    // ONSET
    onset.setup();
    ofAddListener(onset.gotOnset, this, &ofApp::onsetEvent);

    // PITCH
    pitch.setup();

    // BEAT
    beat.setup();
    ofAddListener(beat.gotBeat, this, &ofApp::beatEvent);

    // MEL BANDS
    bands.setup();

    // SOUNDSTREAM
    samplesLeft.resize(512);
    samplesRight.resize(512);

    // Arguments: nOutputs, nInputs, sampleRate, bufferSize, nBuffers
    // If you want to list devices:  (microphone is standard)
    //     ofSoundStream soundStream;

    // Input stream
    soundStream.printDeviceList(); // check this if doesn't work
    
    if (mode == MIC_SPEAKER) {
         soundStream.setDeviceID(MIC_IN); // microphone
         soundStream.setup(this, 0, 1, 44100, 512, 4); // two channel microphone in
    } else {
         soundStream.setDeviceID(SOUND_FLOWER_IN_OUT); // sound flower
         soundStream.setup(this, 0, 2, 44100, 512, 4); // two channel in from soundcard via soundflower
    }
    soundStream.setInput(this);

    // Output stream (to speakers)
    outputStream.setDeviceID(1); // default mac output
    outputStream.setup(this, 2, 0, 44100, 512, 4);
    outputStream.setOutput(this);

    cout << "num input channels:" << soundStream.getNumInputChannels() << endl;

    // ----------------
    // GUI
    // ----------------
    int start = 0;
    beatGui.setup("ofxAubioBeat", "settings.xml", start + 10, 10);
    beatGui.add(bpm.setup( "bpm", 0, 0, 250));

    start += 250;
    onsetGui.setup("ofxAubioOnset", "settings.xml", start + 10, 10);
    onsetGui.add(onsetThreshold.setup( "threshold", 0, 0, 2));
    onsetGui.add(onsetNovelty.setup( "onset novelty", 0, 0, 10000));
    onsetGui.add(onsetThresholdedNovelty.setup( "thr. novelty", 0, -1000, 1000));
    onsetThreshold = onset.threshold; // set default value

    start += 250;
    pitchGui.setup("ofxAubioPitch", "settings.xml", start + 10, 10);
    pitchGui.add(midiPitch.setup( "midi pitch", 0, 0, 128));
    pitchGui.add(pitchConfidence.setup( "confidence", 0, 0, 1));

    bandsGui.setup("ofxAubioMelBands", "settings.xml", start + 10, 115);
    for (int i = 0; i < 40; i++) {
     bandPlot.addVertex( 50 + i * 650 / 40., 240 - 100 * bands.energies[i]);
    }
    // ----------------
    // VISUALISATION GUI
    // ----------------
    visGui.setup("Visualisation GUI", "settings.xml", 550, 300);
    addLayerButton.addListener(this, &ofApp::addLayerButtonPressed);
    addLayerFrontButton.addListener(this, &ofApp::addLayerFrontButtonPressed);
    deleteAllLayersButton.addListener(this, &ofApp::deleteAllLayersButtonPressed);
    deleteFirstButton.addListener(this, &ofApp::deleteFirstButtonPressed);
    deleteLastButton.addListener(this, &ofApp::deleteLastButtonPressed);
    visGui.add(addLayerButton.setup("Add layer"));
    visGui.add(addLayerFrontButton.setup("Add layer in front"));
    visGui.add(deleteAllLayersButton.setup("Delete all layers"));
    
    visGui.add(deleteFirstButton.setup("Delete from front"));
    visGui.add(deleteLastButton.setup("Delete from back"));
    
    visGui.add(LayerType1.set("Layer type 1", false));
    visGui.add(LayerType2.set("Layer type 2", false));
    visGui.add(LayerType3.set("Layer type 3", true));
    visGui.add(LayerType4.set("Layer type 4", false));
    visGui.add(onsetSignalType.set("Signal type onset", true));
    visGui.add(beatSignalType.set("Signal type beat", false));
    visGui.add(blendModeOn.set("BlendMode on", false));
    visGui.add(Subtract.set("Subtract on", false));
    visGui.add(nCols.set("nCols", 1, 1, 6)); // name, value, min, max
    visGui.add(nRows.set("nRols", 2, 1, 6));
    layerType = 3; // set to layer 3 by default
    signalType = 0; // onset
}

void ofApp::handleSelectedParams() {
    // KEEP LAYER TYPES MUTUALLY EXCLUSIVE
    if ((LayerType1) && !(layerType == 1)) {
        layerType = 1;
        LayerType2.set(false);
        LayerType3.set(false);
        LayerType4.set(false);
    }
    if ((LayerType2) && !(layerType == 2)) {
        layerType = 2;
        LayerType1.set(false);
        LayerType3.set(false);
        LayerType4.set(false);
    }
    if ((LayerType3) && !(layerType == 3)) {
        layerType = 3;
        LayerType1.set(false);
        LayerType2.set(false);
        LayerType4.set(false);
    }
    if ((LayerType4) && !(layerType == 4)) {
        layerType = 4;
        LayerType1.set(false);
        LayerType2.set(false);
        LayerType3.set(false);
    }
        
    // BEAT ONSET PARAMS MUTUALLY EXCLUSIVE
    if ((onsetSignalType) && !(signalType == 0)) {
        signalType = 0;
        beatSignalType.set(false);
    }
    if ((beatSignalType) && !(signalType == 1)) {
        signalType = 1;
        onsetSignalType.set(false);
    }
}

void ofApp::plot(vector<float>& buffer, float scale, float offset) {
    ofNoFill();
    int n = buffer.size();
    ofDrawRectangle(0, 0, n, plotHeight);
    glPushMatrix();
    glTranslatef(0, plotHeight / 2 + offset, 0);
    ofBeginShape();
    for (int i = 0; i < n; i++) {
        ofVertex(i, buffer[i] * scale);
    }
    ofEndShape();
    glPopMatrix();
}

void ofApp::update_GUI_SOUND(){
//    cout << "GUI SOUND UPDATE" << endl;
    onset.setThreshold(onsetThreshold);
    
    
}

void ofApp::draw_GUI_SOUND(ofEventArgs & args){
//    cout << "GUI SOUND DRAW" << endl;
    ofBackground(0);
    
    // DRAW GUI
    visGui.draw();
    
    // update beat info
    if (gotBeat) {
        ofSetColor(ofColor::green);
        ofDrawRectangle(90,150,50,50);
//        gotBeat = false;
    }
    string kick = "kick: " + ofToString(beat_ofx.kick());
    string snare = " snare: " + ofToString(beat_ofx.snare());
    string hihat = " hihat: " + ofToString(beat_ofx.hihat());
    
    string m = kick + snare + hihat;
    ofDrawBitmapString(m, 40, 130);
    
    if (beat_ofx.kick() > 0.5) {
        ofDrawRectangle(40,150,20,20);
    }
    
    if (beat_ofx.snare() > 0.5) {
        ofDrawRectangle(70,150,20,20);
    }
    
    if (beat_ofx.kick() > 0.5) {
        ofDrawRectangle(100,150,20,20);
    }
    

    // update onset info
    if (gotOnset) {
        ofSetColor(ofColor::red);
        ofDrawRectangle(250 + 90,150,50,50);
//        gotOnset = false;
    }
    
    onsetNovelty = onset.novelty;
    onsetThresholdedNovelty = onset.thresholdedNovelty;

    // update pitch info
    pitchConfidence = pitch.pitchConfidence;
    if (pitch.latestPitch) midiPitch = pitch.latestPitch;
    bpm = beat.bpm;

    // draw
    pitchGui.draw();
    beatGui.draw();
    onsetGui.draw();

    ofSetColor(ofColor::orange);
    ofSetLineWidth(3.);
    bandsGui.draw();
    bandPlot.clear();
    for (int i = 0; i < bandPlot.size(); i++) {
        bandPlot[i].y = 240 - 100 * bands.energies[i];
    }
    bandPlot.draw();
    
    // PART 2
    // 1 GET DATA TO DRAW (make a snapshot of the current buffer)
    // Freeze the sound buffer into a draw buffer (happens in a different thread)
    soundMutex.lock();
    drawBuffer = middleBuffer;
    drawBins = middleBins;
    soundMutex.unlock();
    
    // 2 PREPARE FOR DRAW
    ofSetColor(255);
    ofPushMatrix();
    
    // 3 DRAW TIME DOMAIN
    ofTranslate(16, 16+250);
    ofDrawBitmapString("Time Domain", 0, 0);
    plot(drawBuffer, plotHeight / 2, 0);
    
    // 4 DRAW FREQUENCY DOMAIN
    ofTranslate(0, plotHeight + 16);
    ofDrawBitmapString("Frequency Domain", 0, 0);
    plot(drawBins, -plotHeight, plotHeight / 2);
    
    // 5 DRAW THE SPECTOGRAM
    ofTranslate(0, plotHeight + 16);
    ofDrawBitmapString("Spectrogram", 0, 0);
    // should be called after you have changed the image' pixel,
    // to reflect the change in the texture to be drawn
    spectrogram.update();
    spectrogram.draw(0, 0);
    ofDrawRectangle(0, 0, bufferSize, bufferSize / 2);
    
    // 6 END DRAW
    ofPopMatrix(); // go back to normal coordinate system
    
    // 7 PRINT THE FRAME RATE
    string msg = ofToString((int) ofGetFrameRate()) + " fps";
    ofDrawBitmapString(msg, ofGetWidth() - 80, ofGetHeight() - 20+250);
    
    if (gotOnset) {
        drawnOnsetGUI = true;
    }
    if (gotBeat) {
        drawnBeatGUI = true;
    }
    ofSetColor(255, 255, 255);
    
    string msg1 = "Layer type: " + ofToString(layerType);
    string s;
    if (signalType == 0) {
        s = "onset";
    } else {
        s = "beat";
    }
    string msg2 = "Signal type: " + s;
    string msg3 = "Num layers: " + ofToString(allLayers.size());
    ofDrawBitmapString(msg1, 550, 285);
    ofDrawBitmapString(msg2, 550, 275);
    ofDrawBitmapString(msg3, 550, 250);
}

void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    beat_ofx.audioReceived(input, bufferSize, nChannels);
    
    for (int i = 0; i < bufferSize; i++) {
        samplesLeft[i] = input[2*i];
        samplesRight[i] = input[2*i+1];
    }
    // ------------------------------------------------------------------
    // PART 1: AUBIO ADDON
    // ------------------------------------------------------------------
    
    // compute onset detection
    onset.audioIn(input, bufferSize, nChannels);
    // compute pitch detection
    pitch.audioIn(input, bufferSize, nChannels);
    // compute beat location
    beat.audioIn(input, bufferSize, nChannels);
    // compute bands
    bands.audioIn(input, bufferSize, nChannels);
    
    // ------------------------------------------------------------------
    // PART 2: OFXFFT ADDON
    // ------------------------------------------------------------------
    
    // 1 STORE AND SCALE THE AUDIO INPUT IN BUFFER ------------------------
    // store input in audioInput buffer
    memcpy(&audioBuffer[0], input, sizeof(float) * bufferSize);
    
    // Get the max absolute value of the audioBuffer
    float maxValue = 0;
    for(int i = 0; i < bufferSize; i++) {
        if(abs(audioBuffer[i]) > maxValue) {
            maxValue = abs(audioBuffer[i]);
        }
    }
    //    cout << "max buffer val:" << maxValue << endl;
    // Normalise it with that max value (to get numbers between -1 and 1)
    for(int i = 0; i < bufferSize; i++) {
        audioBuffer[i] /= maxValue;
    }
    // ------------------------------------------------------------------
    // 2 DO FOURIER TRANSFORM ON THE BUFFER AND COPY IT IN THE BINS ARRAY -
    // Get the bins, not sure how
    fft->setSignal(&audioBuffer[0]);
    float* curFft = fft->getAmplitude();
    memcpy(&audioBins[0], curFft, sizeof(float) * fft->getBinSize());

    // Scale the bins by max value (to get numbers between -1 and 1
    maxValue = 0;
    for(int i = 0; i < fft->getBinSize(); i++) {
        if(abs(audioBins[i]) > maxValue) {
            maxValue = abs(audioBins[i]);
        }
    }
    for(int i = 0; i < fft->getBinSize(); i++) {
        audioBins[i] /= maxValue;
    }

    // ------------------------------------------------------------------
    // 3 UPDATE THE SPECTOGRAM
    int spectrogramWidth = (int) spectrogram.getWidth();
    int n = (int) spectrogram.getHeight();

    // Do a log transform on the bins (because frequencies are binned)
    // but we perceive sound logarithmically
    for(int i = 0; i < n; i++) {
        // value, input range, output range
        int logi = ofMap(powFreq(i), powFreq(0), powFreq(n), 0, n);
        spectrogram.setColor(spectrogramOffset, (n - i - 1), (unsigned char) (255. * audioBins[logi]));
    }
    
    // wrap around if drawn the last column
    spectrogramOffset = (spectrogramOffset + 1) % spectrogramWidth;
    
    // ------------------------------------------------------------------
    // 4 STOP THE AUDIO THREAD TO COPY DATA FOR A MOMENT
    soundMutex.lock();
    middleBuffer = audioBuffer;
    middleBins = audioBins;
    soundMutex.unlock();
}

void ofApp::audioOut(float *output, int bufferSize, int nChannels){
    // Only output sound if channeled from soundcard to this programme
    // and then to output. Not if sound is picked up from mic. Then
    // there already is sound.
    if (mode == SOUNDCARD_SPEAKER) {
        for (int i = 0; i < bufferSize; i++) {
            output[2*i] = samplesLeft[i];
            output[2*i+1] = samplesRight[i];
        }
    }
}

//----
void ofApp::onsetEvent(float & time) {
    gotOnset = true;
    drawnOnsetGUI = false;
    drawnOnsetVIS = false;
}

//----
void ofApp::beatEvent(float & time) {
    gotBeat = true;
    drawnBeatGUI = false;
    drawnBeatVIS = false;
}

void ofApp::exit(){
    ofSoundStreamStop();
    ofSoundStreamClose();
}

