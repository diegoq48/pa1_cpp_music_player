#include "ofApp.h"
#include <ctime>



void ofApp::drawMode0(vector<float> amplitudes)
{
    ofFill();
    ofSetColor(00, 00, color);


    for (int i = 32; i >= 0; i--)
    {
        shownAmplitude = (amplitudes[32 - (i + 1)] * 10 * heightRatio);
        if (fabs(amplitudes[32 - (i + 1)] * 10) > ofGetHeight() - 20)
        {
            shownAmplitude = ((ofGetHeight() - 20) * -1);
        }
        ofDrawRectRounded(ofGetWidth() / 64 * i, ofGetHeight(), ofGetWidth() / 64, shownAmplitude, 5);
    }


    for (int i = 32; i < 64; i++)
    {
        shownAmplitude = (amplitudes[i - 32] * 10 * heightRatio);
        if (fabs(amplitudes[i - 32] * 10) > ofGetHeight() - 20)
        {
            shownAmplitude = (ofGetHeight() - 20) * -1;
        }
        ofDrawRectRounded(ofGetWidth() / 64 * i, ofGetHeight(), ofGetWidth() / 64, shownAmplitude, 5);
    }
}




void ofApp::drawMode1(vector<float> amplitudes)
{
    ofSetLineWidth(5);
    ofNoFill();
    ofSetColor(color, 00, 00);
    int bands = amplitudes.size();
    for (int i = 0; i < bands; i++)
    {
        ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, amplitudes[i] * 10 * heightRatio);
    }
}




void ofApp::drawMode2(vector<float> amplitudes)
{
    ofSetColor(00, color, 00);
    ofFill();
    for (int i = 64; i > 0; i--)
    {
        shownAmplitude = amplitudes[i] * -10 * heightRatio;
        if (amplitudes[i] * -10 * heightRatio > ofGetWidth() / 2)
        {
            shownAmplitude = (ofGetWidth() / 2) -10;
        }
        
        ofDrawRectangle(0, (ofGetHeight() - (20 * i)), shownAmplitude, ofGetHeight() / 64);
    }
    for (int i = 64; i > 0; i--)
    {
        shownAmplitude = amplitudes[i] * -10 * heightRatio;
        if (amplitudes[i] * -10 * heightRatio > ofGetWidth() / 2)
        {
            shownAmplitude = (ofGetWidth() / 2)-10;
        }

        ofDrawRectangle(ofGetWidth(), (ofGetHeight() - (20 * i)), shownAmplitude * -1, ofGetHeight() / 64);
    }
}




void ofApp::drawHelp()
{
    ofSetColor(255);
    int helpMidScreenY = ofGetHeight() / 2 - 48;
    int helpMidScreenX = ofGetWidth() / 2;
    ofDrawBitmapString("Press 'p' to play/pause", helpMidScreenX - strlen("Press 'p' to play/pause") / 2 * 8, (helpMidScreenY));
    ofDrawBitmapString("Press '0' to switch to mode 0", helpMidScreenX - strlen("Press '0' to switch to mode 0") / 2 * 8, helpMidScreenY + 15);
    ofDrawBitmapString("Press '1' to switch to mode 1", helpMidScreenX - strlen("Press '1' to switch to mode 1") / 2 * 8, helpMidScreenY + 30);
    ofDrawBitmapString("Press '2' to switch to mode 2", helpMidScreenX - strlen("Press '2' to switch to mode 2") / 2 * 8, helpMidScreenY + 45);
    ofDrawBitmapString("Press '3' to switch to mode 3", helpMidScreenX - strlen("Press '3' to switch to mode 3") / 2 * 8, helpMidScreenY + 60);
    ofDrawBitmapString("Press 'a' to stop", helpMidScreenX - strlen("Press 'a' to stop") / 2 * 8, helpMidScreenY + 75);
    ofDrawBitmapString("Press 'd' to play next song", helpMidScreenX - strlen("Press 'd' to play next song") / 2 * 8, helpMidScreenY + 90);
    ofDrawBitmapString("Press '=' to increase volume", helpMidScreenX - strlen("Press '=' to increase volume") / 2 * 8, helpMidScreenY + 105);
    ofDrawBitmapString("Press '-' to decrease volume", helpMidScreenX - strlen("Press '-' to decrease volume") / 2 * 8, helpMidScreenY + 120);
    ofDrawBitmapString("Release 'h' to toggle help", helpMidScreenX - strlen("Release 'h' to toggle help") / 2 * 8, helpMidScreenY + 135);
    ofDrawBitmapString("Press 'l' to toggle loop", helpMidScreenX - strlen("Press 'l' to toggle loop") / 2 * 8, helpMidScreenY + 150);
    ofDrawBitmapString("Press 'r' to toggle repeat", helpMidScreenX - strlen("Press 'r' to toggle repeat") / 2 * 8, helpMidScreenY + 165);
    ofDrawBitmapString("Press 'b' to play random song", helpMidScreenX - strlen("Press 'b' to play random song") / 2 * 8, helpMidScreenY + 180);
    ofDrawBitmapString("Press '->' to skip 5 seconds", helpMidScreenX - strlen("Press '->' to skip 5 seconds") / 2 * 8, helpMidScreenY + 195);
    ofDrawBitmapString("Press '<-' to go back 5 seconds", helpMidScreenX - strlen("Press '<-' to go back 5 seconds") / 2 * 8, helpMidScreenY + 210);
    ofDrawBitmapString("Press 'z' to go back 1 song", helpMidScreenX - strlen("Press 'z' to go back 1 song") / 2 * 8, helpMidScreenY + 225);
}




void ofApp::drawHud()
{
    ofSetColor(255);
    ofDrawBitmapString("Mode: " + modeArray[mode], 0, 15);
    ofDrawBitmapString("Song Title: " + songArray[songNumber], 0, 30);
    ofDrawBitmapString("Progress: " + to_string(progress * 100) + "%", 0, 45);
    ofDrawBitmapString("loopStatus: " + to_string(loopStatus), 0, 60);
    ofDrawBitmapString("Repeat: " + to_string(repeatStatus), 0, 75);
    ofDrawBitmapString("Volume: " + to_string(sound.getVolume()), 0, 90);
    ofDrawBitmapString("Press h for help", ofGetWidth() - strlen("Press h for help") * 8, 15);
    ofDrawBitmapString("Mode 0: Bar Graph", ofGetWidth() - strlen("Mode 0: Bar Graph") * 8, 30);
    ofDrawBitmapString("Mode 1: Circle Graph", ofGetWidth() - strlen("Mode 1: Circle Graph") * 8, 45);
    ofDrawBitmapString("Mode 2: Line Graph", ofGetWidth() - strlen("Mode 2: Line Graph") * 8, 60);
    ofDrawBitmapString("Mode 3: 3D Graph", ofGetWidth() - strlen("Mode 3: 3D Graph") * 8, 75);
}

void ofApp::drawMode3(vector<float> amplitudes)
{
    setup3D(true);
    ofSetColor(0, 0, color);
    for (int i = 0; i < 64; i++)
    {
        if (amplitudes[i] < 0)
        {
            // Draws a voxel-like circle for each amplitude
            ofDrawBox(ofPoint(20*i,0,0),20, amplitudes[i] * 8 , amplitudes[i] * 4);
            ofDrawBox(ofPoint(20*i,0,0),20, amplitudes[i] * 6 , amplitudes[i] * 6);
            ofDrawBox(ofPoint(20*i,0,0),20, amplitudes[i] * 4 , amplitudes[i] * 8);
        }
    }
    setup3D(false);
}

void ofApp::setup3D(bool doSetup)
{
    if (doSetup)
    {
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
    }
    else
    {
        setupLighting(light1, false);
        setupLighting(light2, false);
        ofPopMatrix();
        ofPopStyle();
        cam.end();
    }

};

void ofApp::setupLighting(ofLight& light, bool doSetup){
    if (doSetup)
    {
        // Adjust the light for the most even lighting
        light.setDirectional();
        light.setSpotlight();
        light.setSpotlightCutOff(2000);
        light.setSpotConcentration(1);
        light.setPointLight();
        ofEnableDepthTest();
    }
    else
    {
        ofDisableLighting();
        ofDisableDepthTest();
        light.disable();
    }
}
 



void ofApp::drawProgressBar(float pos)
{
    ofFill();
    ofSetColor(255);
    ofDrawRectangle(0, ofGetHeight() - 10, ofGetWidth() * pos, 20);
}



void ofApp::setAmplitude()
{
    if (!barPause)
    {
        lastAmplitudes = amplitudes;
        amplitudes = visualizer.getAmplitudes();
        return;
    }
    amplitudes = lastAmplitudes;
}




void ofApp::changeSong(int displacement)
{
    sound.unload();
    songNumber = songNumber + displacement;
    if ((songNumber > songArraySize || songNumber < 0) && loopStatus)
    {
        songNumber = 0;
        sound.load(songArray[songNumber]);
        sound.play();
    }
    else if ((songNumber > songArraySize || songNumber < 0) && !loopStatus)
    {
        songNumber = 0;
        sound.unload();
        sound.stop();
        playing = false;
        sound.load(songArray[songNumber]);
    }
    else
    {
        sound.load(songArray[songNumber]);
        sound.play();
    }
}




void ofApp::keyPressed(int key)
{
    switch (key)
    {
    case 'p':
        if (playing)
        {
            lastPos = progress;
            sound.stop();
            playing = !playing;
            break;
        }

        sound.setPosition(lastPos);
        sound.play();
        playing = !playing;
        break;

    case '0':
        mode = 0; break;
    case '1':
        mode = 1; break;
    case '2':
        mode = 2; break;
    case '3':
        mode = 3; break;
    case 'a':
        barPause = !barPause; break;
    case 'd':
        playing = true;
        ofApp::changeSong(1);
        break;
    case '=':
        if ((sound.getVolume() == 2.0))
        {
            break;
        }
        sound.setVolume(sound.getVolume() + 0.1);
        break;
    case '-':
        if ((sound.getVolume() == 0.0))
        {
            break;
        }
        sound.setVolume(sound.getVolume() - 0.1);
        break;
    case 'b':
        sound.unload();
        srand(time(NULL));
        songNumber = rand() % songArraySize;
        sound.load(songArray[songNumber]);
        break;
    case 'r':
        repeatStatus = !repeatStatus;
        sound.setLoop(repeatStatus);
        break;
    case 'l':
        loopStatus = !loopStatus; break;
    case 'h':
        helpStatus = !helpStatus; break;
    case 'f':
        ofToggleFullscreen(); break;
    case 'z':
        playing = true; 
        ofApp::changeSong(-1);
        break;
    case OF_KEY_RIGHT:
        sound.setPosition(sound.getPosition() + 0.005); break;
    case OF_KEY_LEFT:
        sound.setPosition(sound.getPosition() - 0.005); break;
    default:
        break;
    }
}

void ofApp::keyReleased(int key)
{
}

void ofApp::mouseMoved(int x, int y)
{
}

void ofApp::mouseDragged(int x, int y, int button)
{
    if (y >= ofGetHeight() - 10 && button == 0)
    {
        float posf = (float)x / (float)ofGetWidth();
        sound.setPosition(posf);
    }
}

void ofApp::mousePressed(int x, int y, int button)
{
    if (y >= ofGetHeight() - 10 && button == 0)
    {
        float posf = (float)x / (float)ofGetWidth();
        sound.setPosition(posf);
    }
}

void ofApp::mouseReleased(int x, int y, int button)
{
}

void ofApp::mouseEntered(int x, int y)
{
}

void ofApp::mouseExited(int x, int y)
{
}

void ofApp::windowResized(int w, int h)
{
    heightRatio = ofGetHeight() / priorScreenHeight;
    priorScreenHeight = ofGetHeight();
}

void ofApp::gotMessage(ofMessage msg)
{
}

void ofApp::dragEvent(ofDragInfo dragInfo)
{
}


void ofApp::setup()
{
    sound.load(songArray[0]);
    sound.setLoop(false);
    sound.setVolume(2);
    ofSetBackgroundColor(00, 00, 00);
    ofSetWindowTitle("Music Player");
}

void ofApp::update()
{
    ofSoundUpdate();
    visualizer.updateAmplitudes();
    progress = sound.getPosition();
    if (progress > 0.99 && !repeatStatus)
    {
        ofApp::changeSong(1);
    }
}

void ofApp::draw()
{

    
    if (ofGetHeight() > 199 && ofGetWidth() > 199)
    {
        ofSetColor(255);
        float pos = playing ? progress : lastPos;
        if (!playing)
        {
            ofDrawBitmapString("Press 'p' to play some music!", (ofGetWidth() / 2) - strlen("Press 'p' to play some music!")*8, ofGetHeight() / 2);
        }
        ofApp::setAmplitude();
        switch (mode)
        {
        case 0:
            drawMode0(amplitudes);
            break;
        case 1:
            drawMode1(amplitudes);
            break;
        case 2:
            drawMode2(amplitudes);
            break;
        case 3:
            drawMode3(amplitudes);
            break;
        default:
            break;
        }
        if (helpStatus)
        {
            ofApp::drawHelp();
        }
        ofApp::drawHud(); 
        ofApp::drawProgressBar(pos);
        return; 
    }
    ofSetColor(255);
    for(int i = 0; i > 0;i++)
    {
        ofDrawBitmapString("Please resize your window",strlen("Please resize your window")*8, ofGetHeight()-(i*10));
    }
}
