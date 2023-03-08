#include "ofApp.h"


// called in update in order to get the amplitude for the given frame 
void ofApp::setAmplitude()
{
    if (!barPause) {
        lastAmplitudes = amplitudes;
        amplitudes = visualizer.getAmplitudes();
    } else {
        // uses the same amplitudes in order to pause the bars 
        amplitudes = lastAmplitudes;
    }
}

// function that allows the app to change songs given a displacement (positive or negative)
void ofApp::changeSong(int displacement)
{
    drawingCollection = false;
    float volume = sound.getVolume();
    // returns if the user is repeating the song function change is handled by sound.loop()
    if (repeatStatus){
        sound.unload();
        sound.load(songVector[songNumber]);
        sound.play();
        sound.setVolume(volume);
        return;
    }
    
    sound.stop();
    sound.unload();
    songNumber += displacement;

    // checks if the song number is out of bounds and if it is it will start over from the beginning
    if (songNumber >= songVectorSize || songNumber < 0) {
        songNumber = 0;
        sound.load(songVector[songNumber]);
        sound.play();
        playing = true; 
        ofLog(OF_LOG_NOTICE, "Song number: " + ofToString(songNumber));
        ofLog(OF_LOG_NOTICE, "Song loaded: " + songVector[songNumber].getFileName());
        sound.setVolume(volume);
        return;

    }
    // default case simply loads the song + displacement and plays it
    playing = true;
    ofLog(OF_LOG_NOTICE, "Song number: " + ofToString(songNumber));
    sound.load(songVector[songNumber]);
    sound.play();
    ofLog(OF_LOG_NOTICE, "Song loaded: " + songVector[songNumber].getFileName());
    sound.setVolume(volume);
}

// set a random song from the song vector
void ofApp::setRandomSong(){
    float volume = sound.getVolume();
    sound.stop();
    sound.unload();
    srand(time(NULL));
    songNumber = rand() % songVectorSize;
    sound.load(songVector[songNumber]);
    sound.play();
    sound.setVolume(volume);
    playing = true; 
    ofLog(OF_LOG_NOTICE, "Song number: " + ofToString(songNumber));
    ofLog(OF_LOG_NOTICE, "Song loaded: " + songVector[songNumber].getFileName());
    return;
}

// sets the playback mode of the app, toggling between repeat, loop and shuffle
void ofApp::setPlaybackMode(char playbackMode) {
    switch (playbackMode) {
        case 'r':
            loopStatus = false;
            shuffleStatus = false;
            repeatStatus = !repeatStatus;
            sound.setLoop(repeatStatus);
            ofLog(OF_LOG_NOTICE, "Repeat Status = " + to_string(repeatStatus));
            break;
        case 'l':
            repeatStatus = false;
            shuffleStatus = false;
            loopStatus = !loopStatus;
            ofLog(OF_LOG_NOTICE, "Loop Status = " + to_string(loopStatus));
            break;
        case 's':
            loopStatus = false;
            repeatStatus = false;
            shuffleStatus = !shuffleStatus;
            ofLog(OF_LOG_NOTICE, "Shuffle Status = " + to_string(shuffleStatus));
            break;
        default:
            repeatStatus = false;
            loopStatus = true;
            shuffleStatus = false;
            break;
    }
}