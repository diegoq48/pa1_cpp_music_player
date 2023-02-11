#include "ofApp.h"
#include <ctime>

//--------------------------------------------------------------
void ofApp::setup(){
    sound.load(songArray[rand() % songArraySize]); //Loads a sound file (in bin/data/)
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
    int percent = pos*100;
    ofDrawBitmapString("Song Progress: " + ofToString(percent) + "%", 0, 30);
    // Mode Selection
    if(!playing){
        ofDrawBitmapString("Press 'p' to play some music!", ofGetWidth()/2 - 50, ofGetHeight()/2);
    }
    vector<float> amplitudes = visualizer.getAmplitudes();
    if(mode == '1'){
        drawMode1(amplitudes);
    }else if(mode == '2'){
        drawMode2(amplitudes);
    }else if(mode == '3'){
        drawMode3(amplitudes);
    }

    // ofDrawBitmapString("Current Mouse Position: " + ofToString(cur_x) + ", " + ofToString(cur_y), 0, 30);

    
}
void ofApp::drawMode1(vector<float> amplitudes){
        ofFill(); // Drawn Shapes will be filled in with color
        ofSetColor(255); // This resets the color of the "brush" to white
        ofDrawBitmapString("Rectangle Height Visualizer", 0, 15);
        // used random color declared in the .h file to change the color of the visualizer to a random shade of blue
        ofSetColor(00, 00, color); 
        //Implemented a mirror bar graph visualizer using two for loops 
        // one for the left side of the screen and one for the right side
        // based on the array of 64 visualizers and itterating as such 
        for (int i = 32; i >= 0; i--) {
            ofDrawRectRounded(ofGetWidth() / 64 * i, ofGetHeight()+5, ofGetWidth()/64,  amplitudes[32 - (i + 1)]*10, 5);
        }
        for (int i = 32; i < 64; i++) { 
            ofDrawRectRounded(ofGetWidth() / 64 * i, ofGetHeight()+5, ofGetWidth()/64,  amplitudes[i-32]*10, 5);

        }  
}
void ofApp::drawMode2(vector<float> amplitudes){
        ofSetLineWidth(5); // Sets the line width
        ofNoFill(); // Only the outline of shapes will be drawn
        ofSetColor(254); // This resets the color of the "brush" to white
        ofDrawBitmapString("Circle Radius Visualizer", 0, 15);
        int bands = amplitudes.size();
        for(int i=0; i< bands; i++){
            ofSetColor((bands - i)*32 %256,18,144); // Color varies between frequencies
        }
        for (int i = 0; i < bands; i++) {
            ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2, amplitudes[i]*100);
        }
}
void ofApp::changeSong(){
    sound.unload();
    songNumber++;
    if (songNumber > songArraySize){songNumber = 0;}
    sound.load(songArray[songNumber]);
    sound.play();
}

void ofApp::drawMode3(vector<float> amplitudes){
    ofSetColor(254); // This resets the color of the "brush" to white
    ofDrawBitmapString("Rectangle Width Visualizer", 0, 15);
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
                sound.stop();
            }else{
                sound.play();               
            }
            playing = !playing;
            break;
        case '1':
            mode = '1';
            break;
        case '2':
            mode = '2';
            break;
        case '3':
            mode = '3';
            break;
        case 'a':
            sound.stop();
            break;
        case 'd':
        //case to play next song
            ofApp::changeSong();
            break; 
        case '=':
            //case to increase volume
            sound.setVolume(sound.getVolume() + 0.1);   
            break;
        case '-':
            //case to decrease volume
            sound.setVolume(sound.getVolume() - 0.1);
            break;
        case 'r':
            // play a random song 
            sound.unload();
            sound.load(songArray[rand() % songArraySize]);
            sound.play();
            break;
        case 'l':
            //loop song 
            if (sound.isLoaded()){
                sound.setLoop(false);
            }else{
                sound.setLoop(true);
            }
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    cur_x = x;
    cur_y = y;
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