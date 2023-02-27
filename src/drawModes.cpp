#include "ofApp.h"


void ofApp::drawMode1(vector<float> amplitudes)
{
    ofFill();
    ofSetColor(00, 00, color);
    int windowHeight = ofGetHeight();
    int windowWidth = ofGetWidth();
    for (int i = 32; i >= 0; i--)
    {
        // Multiplies the amplitude by a constant to make the bars bigger along with the height Ratio
        shownAmplitude = (amplitudes[32 - (i + 1)] * 10 * heightRatio);
        // Truncates the bars at windowHeight -20
        if (fabs(amplitudes[32 - (i + 1)] * 10) > windowHeight - 20)
        {
            shownAmplitude = ((windowHeight - 20) * -1);
        }
        ofDrawRectRounded(windowWidth / 64 * i, windowHeight +10, windowWidth / 64, shownAmplitude, 5);
    }


    for (int i = 32; i < 64; i++)
    {
        // Multiplies the amplitude by a constant to make the bars bigger along with the height Ratio
        shownAmplitude = (amplitudes[i - 32] * 10 * heightRatio);
        // Truncates the bars at windowHeight -20 
        if (fabs(amplitudes[i - 32] * 10) > windowHeight - 20)
        {
            shownAmplitude = (windowHeight - 20) * -1;
        }
        ofDrawRectRounded(windowWidth / 64 * i, windowHeight+10, windowWidth / 64, shownAmplitude, 5);
    }
}



// Draws multiple circle with the radius being the amplitude of the frequency band and the color being a random shade of red
void ofApp::drawMode2(vector<float> amplitudes)
{
    ofSetLineWidth(5);
    ofNoFill();
    ofSetColor(color, 00, 00);
    int bands = amplitudes.size();
    for (int i = 0; i < bands; i++)
    {
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
    ofFill();
    int windowHeight = ofGetHeight();
    int windowWidth = ofGetWidth();
    for (int i = 64; i > 0; i--)
    {
        // Multiplies the amplitude by a constant to make the bars bigger along with the height Ratio
        shownAmplitude = amplitudes[i] * -10 ;
        // Truncates the bars at the center of the screen
        if (shownAmplitude  > windowHeight / 2)
        {
            shownAmplitude = (windowWidth / 2) -10;
        }
        
        ofDrawRectangle(0, (windowHeight - (32 * i)), shownAmplitude, windowHeight / 64);
    }

    for (int i = 64; i > 0; i--)
    {
        // Multiplies the amplitude by a constant to make the bars bigger along with the height Ratio
        shownAmplitude = amplitudes[i] * -10 ;
        // Truncates the bars at the center of the screen
        if (shownAmplitude  > windowHeight / 2)
        {
            shownAmplitude = (windowWidth / 2) -10;
        }
        
        ofDrawRectangle(windowWidth, (windowHeight - (32 * i)), shownAmplitude*-1, windowHeight / 64);
    }
}

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
 



void ofApp::drawMode4(vector<float> amplitudes){
    setup3D(true);
    ofSetColor(0, 0, color);
    for (int i = 0; i < 64; i++){
        if (amplitudes[i] < 0){
            // Draws a voxel-like circle for each amplitude
            ofDrawBox(ofPoint(20*i,0,0),20, amplitudes[i] * 8 , amplitudes[i] * 4);
            ofDrawBox(ofPoint(20*i,0,0),20, amplitudes[i] * 6 , amplitudes[i] * 6);
            ofDrawBox(ofPoint(20*i,0,0),20, amplitudes[i] * 4 , amplitudes[i] * 8);
        }
    }
    setup3D(false);
}