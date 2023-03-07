#include "ofApp.h"




// called in update in order to get the amplitude for the given frame 
void ofApp::setAmplitude()
{
    if (!barPause)
    {
        lastAmplitudes = amplitudes;
        amplitudes = visualizer.getAmplitudes();
        return;
    }
    // uses the same amplitudes in order to pause the bars 
    amplitudes = lastAmplitudes;
}




// function that allows the app to change songs given a displacement (positive or negative)
void ofApp::changeSong(int displacement)
{
    // returns if the user is repeating the song function change is handled by sound.loop()
    if (repeatStatus){
        return;
    }
    
    sound.stop();
    sound.unload();
    songNumber += displacement;
    // plays a random song using present time as a seed 
    if (shuffleStatus)
    {
        srand(time(NULL));
        songNumber = rand() % songVectorSize;
        sound.load(songVector[songNumber]);
        sound.play();
        playing = true; 
        ofLog(OF_LOG_NOTICE, "Song number: " + ofToString(songNumber));
        ofLog(OF_LOG_NOTICE, "Song loaded: " + songVector[songNumber].getFileName());
        return;
    }

    // checks if the song number is out of bounds and if it is it will start over from the beginning
    if (songNumber >= songVectorSize || songNumber < 0)
    {
        songNumber = 0;
        sound.load(songVector[songNumber]);
        sound.play();
        playing = true; 
        ofLog(OF_LOG_NOTICE, "Song number: " + ofToString(songNumber));
        ofLog(OF_LOG_NOTICE, "Song loaded: " + songVector[songNumber].getFileName());
        return;

    }
    // default case simply loads the song + displacement and plays it
    playing = true;
    ofLog(OF_LOG_NOTICE, "Song number: " + ofToString(songNumber));
    sound.load(songVector[songNumber]);
    sound.play();
    ofLog(OF_LOG_NOTICE, "Song loaded: " + songVector[songNumber].getFileName());
}
