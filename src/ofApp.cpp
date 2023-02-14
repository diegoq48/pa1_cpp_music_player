#include "ofApp.h"
#include <ctime>
#include <typeinfo>

//--------------------------------------------------------------
void ofApp::setup(){
    //sound.load(songArray[rand() % songArraySize]); //Loads a sound file (in bin/data/)
    sound.load(songArray[0]);
    sound.setLoop(false); // Makes the song loop indefinitely
    sound.setVolume(2); // Sets the song volume
    ofSetBackgroundColor(00, 00,00); // Sets the Background Color
    ofSetWindowTitle("Music Visualizer"); // Sets the Window Title
}

//--------------------------------------------------------------
void ofApp::update(){
    /* The update method is called muliple times per second
    It's in charge of updating variables and the logic of our app */
    ofSoundUpdate(); // Updates all sound players
    visualizer.updateAmplitudes(); // Updates Amplitudes for visualizer
    progress = sound.getPosition();
}

//--------------------------------------------------------------
void ofApp::draw(){
    /* The update method is called muliple times per second
    It's in charge of drawing all figures and text on screen */

    // Progress Bar
    ofSetColor(255); 
    ofFill();

    float pos = playing ? progress : lastPos;

    ofFill();

    ofSetColor(100); // Set background bar color
    ofDrawRectangle(0, ofGetHeight() - 20, ofGetWidth(), 20); // Draw background bar

    ofSetColor(255); // Set progress bar and text color
    ofDrawRectangle(0, ofGetHeight() - 20, ofGetWidth() * pos, 20); // Draw progress bar

    // Mode Selection
    if(!playing){
        ofDrawBitmapString("Press 'p' to play some music!", ofGetWidth()/2 - 50, ofGetHeight()/2);
    }
    vector<float> amplitudes = visualizer.getAmplitudes();
    switch(mode){
        case 0:
            drawMode0(amplitudes);
            break;
        case 1:
            drawMode1(amplitudes);
            break;
        case 2:
            drawMode2(amplitudes);
            break;
        default:
            break;
    }
    
}


    void ofApp::changeSong(){
        sound.unload();
        songNumber++;
        if (songNumber > songArraySize && loopStatus){
            songNumber = 0;
            sound.load(songArray[songNumber]);
            sound.play();
        } 
        else if(songNumber > songArraySize && !loopStatus){
            songNumber = 0;
            sound.unload();
            sound.stop();
            playing = false;
            sound.load(songArray[songNumber]);
        }
        else{ 
            sound.load(songArray[songNumber]);
            sound.play();
        }
    }

    void ofApp::drawHud(){
        ofDrawBitmapString("Mode: " + modeArray[mode], 0, 15);
        ofDrawBitmapString("Song Title: " + songArray[songNumber], 0, 30);
        ofDrawBitmapString("Progress: " +  to_string(progress * 100) + "%", 0, 45);
        ofDrawBitmapString("loopStatus: " +  to_string(loopStatus), 0, 60);
        ofDrawBitmapString("Repeat: " +  to_string(repeatStatus), 0, 75);
        ofDrawBitmapString("Volume: " +  to_string(sound.getVolume()), 0, 90);
        ofDrawBitmapString("Press h for help", ofGetWidth() - 100, ofGetHeight() - 5);
    }

    
void ofApp::drawMode0(vector<float> amplitudes){
        ofFill(); // Drawn Shapes will be filled in with color
        ofSetColor(255); // This resets the color of the "brush" to white
        ofSetColor(255); // This resets the color of the "brush" to white
        ofApp::drawHud();
        // used random color declared in the .h file to change the color of the visualizer to a random shade of blue
        ofSetColor(00, 00, color); 
        //Implemented a mirror bar graph visualizer using two for loops 
        // one for the left side of the screen and one for the right side
        // based on the array of 64 visualizers and itterating as such 
        for (int i = 32; i >= 0; i--) {
            if (fabs(amplitudes[32 - (i + 1)]*10) > ofGetHeight() -20){
                shownAmplitude = (ofGetHeight() - 20)*-1;
            }
            else{
                shownAmplitude = amplitudes[32 - (i + 1)]*10;
            }
            ofDrawRectRounded(ofGetWidth() / 64 * i, ofGetHeight()+5, ofGetWidth()/64,  shownAmplitude, 5);
        }
        for (int i = 32; i < 64; i++) { 
            if (fabs(amplitudes[i-32]*10) > ofGetHeight() -20){
                shownAmplitude = (ofGetHeight() - 20)*-1;
            }
            else{
                shownAmplitude = amplitudes[i-32]*10;
            }
            ofDrawRectRounded(ofGetWidth() / 64 * i, ofGetHeight()+5, ofGetWidth()/64,  shownAmplitude, 5);

        }  
}
void ofApp::drawMode1(vector<float> amplitudes){
        ofSetLineWidth(5); // Sets the line width
        ofNoFill(); // Only the outline of shapes will be drawn
        ofSetColor(255); // This resets the color of the "brush" to white
        ofApp::drawHud();
        int bands = amplitudes.size();
        for(int i=0; i< bands; i++){
            ofSetColor((bands - i)*32 %255,18,144); // Color varies between frequencies
        }
        for (int i = 0; i < bands; i++) {
            ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2, amplitudes[i]*100);
        }
}


void ofApp::drawMode2(vector<float> amplitudes){
    ofSetColor(255); // This resets the color of the "brush" to white
    ofApp::drawHud();
    // YOUR CODE HERE
    for (int i = 0; i < 64; i++){
        ofDrawRectangle(ofGetWidth()/64*i, (ofGetHeight()/2) , amplitudes[i]*10, 10);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // This method is called automatically when any key is pressed
    switch(key){
        case 'p':
            if(playing){
                lastPos = progress;
                sound.stop();
            }else{
                sound.setPosition(lastPos);
                sound.play();
            }
            playing = !playing;
            break;
        case '0':
            mode = 0;
            break;
        case '1':
            mode = 1;
            break;
        case '2':
            mode = 2;
            break;
        case 'a':
            sound.stop();
            break;
        case 'd':
        //case to play next song
            ofApp::changeSong();
            break; 
        case '=':
            if ((sound.getVolume() < 0.0) || (sound.getVolume() > 2.0)){
                break;
            }
            else{
                sound.setVolume(sound.getVolume() + 0.1);
            }
            break;
        case '-':
            //case to decrease volume
            if ((sound.getVolume() < 0.0) || (sound.getVolume() > 2.0)){
                break;
            }
            else{
                sound.setVolume(sound.getVolume() - 0.1);
            }
            break;
        case 'b':
            // play a random song 
            sound.unload();
            songNumber = rand() % songArraySize;
            sound.load(songArray[songNumber]);
            sound.play();
            break;
        case 'r':
            repeatStatus = !repeatStatus;
            sound.setLoop(repeatStatus);
            break;
        case 'l':
            loopStatus = !loopStatus;
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
    if (y >= ofGetHeight() - 20 && button == 0) {
        float posf = (float)x / (float)ofGetWidth(); // Get the correct position in the song
        sound.setPosition(posf); // Set the position of the song
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    if (y >= ofGetHeight() - 20 && button == 0) {
        float posf = (float)x / (float)ofGetWidth(); // Get the correct position in the song
        sound.setPosition(posf); // Set the position of the song
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
//--------------------------------------------------------------