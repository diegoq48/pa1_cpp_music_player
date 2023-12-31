#include "ofApp.h"


// Draws one set of bars at the bottom of the window with the width of them being based on the amplitude of the frequency band truncated at the height of the window - 20
// Gets amplitudes until 32 in order to mirror them 
void ofApp::drawMode1(vector<float> amplitudes)
{
    ofSetColor(00, 00, color);
    int windowHeight = ofGetHeight();
    int windowWidth = ofGetWidth();
    float currentVolume = sound.getVolume();
    // left side of the screen
    for (int i = 32; i >= 0; i--) {
        shownAmplitude = (amplitudes[32 - (i + 1)] * 10 * heightRatio) * (currentVolume + 1);
        if (shownAmplitude * -1 > windowHeight - 20) {
            shownAmplitude = ((windowHeight - 20) * -1);
        }
        ofDrawRectRounded(windowWidth / 64 * i, windowHeight-10, windowWidth / 80, shownAmplitude, 5);
    }

    // right side of the screen
    for (int i = 32; i < 64; i++) {
        shownAmplitude = (amplitudes[i - 32] * 10 * heightRatio) * (currentVolume + 1);
        if (shownAmplitude * -1 > windowHeight - 20) {
            shownAmplitude = (windowHeight - 20) * -1;
        }
        ofDrawRectRounded(windowWidth / 64 * i, windowHeight-10, windowWidth / 80, shownAmplitude, 5);
    }
}

// Draws multiple circle with the radius being the amplitude of the frequency band and the color being a random shade of red
void ofApp::drawMode2(vector<float> amplitudes)
{
    ofNoFill();
    ofSetLineWidth(5);
    ofSetColor(color, 00, 00);
    int bands = amplitudes.size();
    for (int i = 0; i < bands; i++) {
        shownAmplitude = amplitudes[i] * 10 * heightRatio;
        ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, shownAmplitude * 10 * heightRatio);
    }
}

// Draws two sets of bars at both sides of the window with the width of them being based on the amplitude of the frequency band
// with a random shade of green being used for the color and the height of the bars being the height of the window divided by 64
// with bars truncated at the center of the screen +- 10 pixels 
void ofApp::drawMode3(vector<float> amplitudes)
{
    ofSetColor(00, color, 00);
    int windowHeight = ofGetHeight();
    int windowWidth = ofGetWidth();

    // left side of the screen
    for (int i = 64; i > 0; i--) {
        shownAmplitude = amplitudes[i] * -10;
        if (shownAmplitude  > windowHeight / 2) {
            shownAmplitude = (windowWidth / 2);
        }
        
        ofDrawRectangle(0, (windowHeight - (32 * i)), shownAmplitude, windowHeight / 64);
    }

    // right side of the screen
    for (int i = 64; i > 0; i--) {
        shownAmplitude = amplitudes[i] * -10;
        if (shownAmplitude  > windowHeight / 2) {
            shownAmplitude = (windowWidth / 2);
        }
        
        ofDrawRectangle(windowWidth, (-32 + (32 * i)), shownAmplitude*-1, windowHeight / 64);
    }
    
}

// Setups the 3D scene for mode 4
void ofApp::setup3D(bool doSetup){
    if (doSetup) {
        // Setup the lighting
        setupLighting(light1, true);
        setupLighting(light2, true);

        // Setup the camera
        cam.setPosition(0, 900, 1000);
        cam.lookAt(glm::vec3(0, 700, 500));
        cam.begin();

        // Setup the lights for even lighting across the scene
        light1.setPosition(0, 500, 1500);
        light2.setPosition(0, 500, -1500);
        light1.draw();
        light2.draw();

        // Setup the scene
        ofPushStyle();
        ofPushMatrix();
        ofRotateDeg(90, 0, 0, 1); // Rotate the whole scene 90 degrees around the z axis to align the boxes vertically
        ofRotateDeg(ofGetElapsedTimef()*50, 0.5, 0, 0); // Rotate the whole scene around the x axis to make it spin

        ofEnableLighting();
        light1.enable();
        light2.enable();
    } else {
        setupLighting(light1, false);
        setupLighting(light2, false);
        ofPopMatrix();
        ofPopStyle();
        cam.end();
    }

};

// Sets up the lighting for mode 4
void ofApp::setupLighting(ofLight& light, bool doSetup){
    if (doSetup) {
        // Adjust the light for the most even lighting
        light.setDirectional();
        light.setSpotlight();
        light.setSpotlightCutOff(2000);
        light.setSpotConcentration(1);
        light.setPointLight();
        ofEnableDepthTest();
    } else {
        ofDisableLighting();
        ofDisableDepthTest();
        light.disable();
    }
}

// Draws a voxel-like circle for each band with the amplitude of the frequency band being the radius of the circle
// Is oriented like a tower
void ofApp::drawMode4(vector<float> amplitudes){
    setup3D(true);
    ofSetColor(0, 0, color);
    for (int i = 0; i < 64; i++) {
        if (amplitudes[i] < 0) {
            ofDrawBox(ofPoint(20*i,0,0),20, amplitudes[i] * 8 , amplitudes[i] * 4);
            ofDrawBox(ofPoint(20*i,0,0),20, amplitudes[i] * 6 , amplitudes[i] * 6);
            ofDrawBox(ofPoint(20*i,0,0),20, amplitudes[i] * 4 , amplitudes[i] * 8);
        }
    }
    setup3D(false);
}