#include "ofApp.h"
#include "ofEventUtils.h"

//--------------------------------------------------------------
void ofApp::setup(){
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
    // Arguments: nOutputs, nInputs, sampleRate, bufferSize, nBuffers
    // If you want to list devices: ofSoundStreamListDevices(); (microphone is standard)
    ofSoundStreamSetup(0, 2, 44100, 512, 4);
    
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
    visGui.setup("Visualisation GUI", "settings.xml", 500, 500);
//    visGui.setup(start, 500);
    visGui.add(addLayerButton.setup("Add layer"));
    
}



float powFreq(float i) {
    // Floating point power to the third
    return powf(i, 3);
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

//--------------------------------------------------------------
void ofApp::update(){
    onset.setThreshold(onsetThreshold);
}

void ofApp::draw_visuals(){
    ofSetColor(ofColor::blue);
    ofFill();
    
    int n_blocks = 20;
    float width = 30.0;
    float neg_width = ofGetWidth()/n_blocks;

    for(int i = 0; i<n_blocks; i++) {
        ofDrawRectangle(i*(width+neg_width), 0, width, ofGetHeight());
    }
    
    // DRAW GUI
    visGui.draw();
}

//--------------------------------------------------------------
// FOR ALL THE GUI STUFF AND STANDARD SOUND STUFF
void ofApp::draw(){
    ofBackground(0, 0, 0);
    
    draw_visuals();
    
    // update beat info
    if (gotBeat) {
        ofSetColor(ofColor::green);
        ofDrawRectangle(90,150,50,50);
        gotBeat = false;
    }

    // update onset info
    if (gotOnset) {
        ofSetColor(ofColor::red);
        ofDrawRectangle(250 + 90,150,50,50);
        gotOnset = false;
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
    //bandPlot.clear();
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
}

void ofApp::audioIn(float * input, int bufferSize, int nChannels){
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

void audioOut(){
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}

//----
void ofApp::onsetEvent(float & time) {
    //ofLog() << "got onset at " << time << " s";
    gotOnset = true;
}

//----
void ofApp::beatEvent(float & time) {
    //ofLog() << "got beat at " << time << " s";
    gotBeat = true;
}

void ofApp::exit(){
    ofSoundStreamStop();
    ofSoundStreamClose();
}
