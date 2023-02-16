#include "ofApp.h"
#include <ctime>

//--------------------------------------------------------------
void ofApp::setup(){
    sound.load(songArray[0]);
    sound.setLoop(false); // Makes the song loop indefinitely
    sound.setVolume(2); // Sets the song volume
    ofSetBackgroundColor(00, 00,00); // Sets the Background Color
    ofSetWindowTitle("Music Visualizer"); // Sets the Window Title
    ofApp::getSongs();
}

//--------------------------------------------------------------
void ofApp::update(){
    /* The update method is called muliple times per second
    It's in charge of updating variables and the logic of our app */
    ofSoundUpdate(); // Updates all sound players
    visualizer.updateAmplitudes(); // Updates Amplitudes for visualizer
    progress = sound.getPosition();
    if (progress > 0.99 && !repeatStatus){
        ofApp::changeSong();
    }
    
}

//--------------------------------------------------------------
//update method draws constants 
void ofApp::draw(){

    ofSetColor(255); 
    ofFill();
    ofApp::drawHud();
    float pos = playing ? progress : lastPos;

    ofFill();

    ofSetColor(0); // Set background bar color
    ofDrawRectangle(0, ofGetHeight() - 20, ofGetWidth(), 20); // Draw background bar

    ofSetColor(255); // Set progress bar and text color
    ofDrawRectangle(0, ofGetHeight() - 20, ofGetWidth() * pos, 20); // Draw progress bar

    // Mode Selection
    if(!playing){
        ofDrawBitmapString("Press 'p' to play some music!", ofGetWidth()/2 - 50, ofGetHeight()/2);
    }
    ofApp::setAmplitude();
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
    ofApp::drawProgressBar(pos);
    if (helpStatus){
        ofApp::drawHelp();
    }
}
    
void ofApp::drawMode0(vector<float> amplitudes){
        ofFill(); // Drawn Shapes will be filled in with color
        ofSetColor(255); // This resets the color of the "brush" to white
        ofSetColor(255); // This resets the color of the "brush" to white
        //ofApp::drawHud();
        // used random color declared in the .h file to change the color of the visualizer to a random shade of blue
        ofSetColor(00, 00, color); 
        //Implemented a mirror bar graph visualizer using two for loops 
        // one for the left side of the screen and one for the right side
        // based on the array of 64 visualizers and itterating as such 
        for (int i = 32; i >= 0; i--) {
            if (fabs(amplitudes[32 - (i + 1)]*10) > ofGetHeight() -20){
                shownAmplitude = ((ofGetHeight() - 20)*-1);
            }
            else{
                shownAmplitude = (amplitudes[32 - (i + 1)]*10 * heightRatio);
            }
            ofDrawRectRounded(ofGetWidth() / 64 * i, ofGetHeight()+5, ofGetWidth()/64,  shownAmplitude, 5);
        }
        for (int i = 32; i < 64; i++) { 
            if (fabs(amplitudes[i-32]*10) > ofGetHeight() -20){
                shownAmplitude = (ofGetHeight() - 20)*-1;
            }
            else{
                shownAmplitude = (amplitudes[i-32]*10* heightRatio);
            }
            ofDrawRectRounded(ofGetWidth() / 64 * i, ofGetHeight()+5, ofGetWidth()/64,  shownAmplitude, 5);
        }  
}
void ofApp::drawMode1(vector<float> amplitudes){
        ofSetLineWidth(5); // Sets the line width
        ofNoFill(); // Only the outline of shapes will be drawn
        ofSetColor(255); // This resets the color of the "brush" to white
        //ofApp::drawHud();
        int bands = amplitudes.size();
        for(int i=0; i< bands; i++){
            ofSetColor((bands - i)*32 %255,18,144); // Color varies between frequencies
        }
        for (int i = 0; i < bands; i++) {
            ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2, amplitudes[i]*100);
        }
}

void ofApp::setAmplitude(){
//  if(outputingUserAudio){
//        amplitudes = visualizer.getUserAmplitudes();
//    }
     if(!barPause){
        lastAmplitudes = amplitudes;
        amplitudes = visualizer.getAmplitudes();
    }
    else{
        amplitudes = lastAmplitudes;
    } 
}


void ofApp::drawMode2(vector<float> amplitudes){
    ofSetColor(255); // This resets the color of the "brush" to white
    for (int i = 0; i < 64; i++){
        ofDrawRectangle(ofGetWidth()/64*i, (ofGetHeight()/2) , amplitudes[i]*10, 10);
    }
}

 void ofApp::getSongs()
{
    std::string dir = "/home/diegoq/Projects/advanced/of_v0.11.2_linux64gcc6_release/apps/myApps/pa1-diegoquinones_edyancruz/bin/data";

    /* if(argv[1])
        dir = argv[1]; */

    for(auto& item: filesystem::recursive_directory_iterator(dir))
    {
        if(!filesystem::is_regular_file(item.path())
        || item.path().extension() != ".mp3" || item.path().extension() != ".wav" || item.path().extension() != ".flac")
            continue;

        // open text file here
            std::cout << item.path() << std::endl; 
    }
} 
 
 void ofApp::drawHelp(){
        int helpMidScreenY = ofGetHeight()/2-48; int helpMidScreenX = ofGetWidth()/2;
        ofDrawBitmapString("Press 'p' to play/pause", helpMidScreenX-strlen("Press 'p' to play/pause")/2*8, (helpMidScreenY));
        ofDrawBitmapString("Press '0' to switch to mode 0", helpMidScreenX-strlen("Press '0' to switch to mode 0")/2 *8, helpMidScreenY +15 );
        ofDrawBitmapString("Press '1' to switch to mode 1", helpMidScreenX-strlen("Press '1' to switch to mode 1")/2 *8, helpMidScreenY +30);
        ofDrawBitmapString("Press '2' to switch to mode 2", helpMidScreenX-strlen("Press '2' to switch to mode 2")/2 *8, helpMidScreenY +45);
        ofDrawBitmapString("Press 'a' to stop", helpMidScreenX-strlen("Press 'a' to stop")/2 *8 , helpMidScreenY+60);
        ofDrawBitmapString("Press 'd' to play next song", helpMidScreenX-strlen("Press 'd' to play next song")/2 *8, helpMidScreenY +75);
        ofDrawBitmapString("Press '=' to increase volume", helpMidScreenX-strlen("Press '=' to increase volume")/2 *8, helpMidScreenY +90);
        ofDrawBitmapString("Press '-' to decrease volume", helpMidScreenX-strlen("Press '-' to decrease volume")/2 *8, helpMidScreenY +105);
        ofDrawBitmapString("Release 'h' to toggle help", helpMidScreenX-strlen("Release 'h' to toggle help")/2 *8, helpMidScreenY +120);
        ofDrawBitmapString("Press 'l' to toggle loop", helpMidScreenX-strlen("Press 'l' to toggle loop")/2 *8, helpMidScreenY+ 135);
        ofDrawBitmapString("Press 'r' to toggle repeat", helpMidScreenX-strlen("Press 'r' to toggle repeat")/2 *8, helpMidScreenY + 150);
        ofDrawBitmapString("Press 'b' to play random song", helpMidScreenX-strlen("Press 'b' to play random song")/2 *8, helpMidScreenY + 165);
} 


    void ofApp::drawProgressBar(float pos){
        ofFill();
        ofSetColor(100); // Set background bar color
        ofDrawRectangle(0, ofGetHeight() - 20, ofGetWidth(), 20); // Draw background bar
        ofSetColor(255); // Set progress bar and text color
        ofDrawRectangle(0, ofGetHeight() - 20, ofGetWidth() * pos, 20); // Draw progress bar

    }


    void ofApp::changeSong(){
        sound.unload();
        songNumber++;
        if (songNumber > songArraySize && loopStatus){
            songNumber = 0;
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
        ofDrawBitmapString("Press h for help", ofGetWidth() - strlen("Press h for help")*8, 15);
        ofDrawBitmapString("Mode 0: Bar Graph", ofGetWidth() - strlen("Mode 0: Bar Graph")*8, 30);
        ofDrawBitmapString("Mode 1: Circle Graph", ofGetWidth() - strlen("Mode 1: Circle Graph")*8, 45);
        ofDrawBitmapString("Mode 2: Line Graph", ofGetWidth() - strlen("Mode 2: Line Graph")*8, 60);
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
            barPause = !barPause;
            break;
        case 'd':
        //case to play next song
            playing = true;
            ofApp::changeSong();
    
            break; 
        case '=':
            if ( (sound.getVolume() == 2.0)){
                break;
            }
            else{
                sound.setVolume(sound.getVolume() + 0.1);
            }
            break;
        case '-':
            //case to decrease volume
            if ((sound.getVolume() < 0.0)){
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
            playing = true;
            break;
        case 'r':
            repeatStatus = !repeatStatus;
            sound.setLoop(repeatStatus);
            break;
        case 'l':
            loopStatus = !loopStatus;
       /*  case 'u':
            sound.unload();
            sound.load(ofSoundStreamSetup(2, 0, 44100, 256, 4), stream=true)
            sound.play();
            break;   */ 
        case 'h':
            helpStatus = !helpStatus;
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
    heightRatio = ofGetHeight() / priorScreenHeight;
    priorScreenHeight = ofGetHeight();
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
//--------------------------------------------------------------