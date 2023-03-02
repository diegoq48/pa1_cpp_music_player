#include "ofApp.h"

void ofApp::drawHelp()
{
    ofSetColor(255);
    int helpMidScreenY = ofGetHeight() / 2 - 48;
    int helpMidScreenX = ofGetWidth() / 2;
    font.drawString("Press 'p' to play/pause", helpMidScreenX - strlen("Press 'p' to play/pause") / 2 * 8, (helpMidScreenY));
    font.drawString("Press '1' to switch to mode 1", helpMidScreenX - strlen("Press '0' to switch to mode 0") / 2 * 8, helpMidScreenY + 15);
    font.drawString("Press '2' to switch to mode 2", helpMidScreenX - strlen("Press '1' to switch to mode 1") / 2 * 8, helpMidScreenY + 30);
    font.drawString("Press '3' to switch to mode 3", helpMidScreenX - strlen("Press '2' to switch to mode 2") / 2 * 8, helpMidScreenY + 45);
    font.drawString("Press '4' to switch to mode 4", helpMidScreenX - strlen("Press '3' to switch to mode 3") / 2 * 8, helpMidScreenY + 60);
    font.drawString("Press 'a' to stop", helpMidScreenX - strlen("Press 'a' to stop") / 2 * 8, helpMidScreenY + 75);
    font.drawString("Press 'd' to play next song", helpMidScreenX - strlen("Press 'd' to play next song") / 2 * 8, helpMidScreenY + 90);
    font.drawString("Press '=' to increase volume", helpMidScreenX - strlen("Press '=' to increase volume") / 2 * 8, helpMidScreenY + 105);
    font.drawString("Press '-' to decrease volume", helpMidScreenX - strlen("Press '-' to decrease volume") / 2 * 8, helpMidScreenY + 120);
    font.drawString("Release 'h' to toggle help", helpMidScreenX - strlen("Release 'h' to toggle help") / 2 * 8, helpMidScreenY + 135);
    font.drawString("Press 'l' to toggle loop", helpMidScreenX - strlen("Press 'l' to toggle loop") / 2 * 8, helpMidScreenY + 150);
    font.drawString("Press 'r' to toggle repeat", helpMidScreenX - strlen("Press 'r' to toggle repeat") / 2 * 8, helpMidScreenY + 165);
    font.drawString("Press 'b' to play random song", helpMidScreenX - strlen("Press 'b' to play random song") / 2 * 8, helpMidScreenY + 180);
    font.drawString("Press '->' to skip 5 seconds", helpMidScreenX - strlen("Press '->' to skip 5 seconds") / 2 * 8, helpMidScreenY + 195);
    font.drawString("Press '<-' to go back 5 seconds", helpMidScreenX - strlen("Press '<-' to go back 5 seconds") / 2 * 8, helpMidScreenY + 210);
    font.drawString("Press 'z' to go back 1 song", helpMidScreenX - strlen("Press 'z' to go back 1 song") / 2 * 8, helpMidScreenY + 225);
    font.drawString("Press 's' to shuffle songs", helpMidScreenX - strlen("Press 's' to shuffle songs") / 2 * 8, helpMidScreenY + 240);
    font.drawString("Press '/' to play a song at a index number", helpMidScreenX - strlen("Press '/' to play a song at a index number") / 2 * 8, helpMidScreenY + 255);
    font.drawString("Press 'k' to reset the song directory", helpMidScreenX - strlen("Press 'k' to reset the song directory") / 2 * 8, helpMidScreenY + 270);
}

void ofApp::drawHud()
{
    std::string shownLoopStatus = loopStatus? "ON":"OFF";
    std::string shownRepeatStatus = repeatStatus? "ON":"OFF";
    std::string shownShuffleStatus = shuffleStatus? "ON":"OFF";
    string nextSong = songNumber + 1 < songVectorSize? songVector[songNumber + 1].getFileName() : "No More Songs";
    ofSetColor(255);
    int currentWidth = ofGetWidth();
    font.drawString("Mode: " + modeArray[mode-1], 0, 15);
    ofSetColor(255,255,0);
    font.drawString("Now Playing: " + (songVector[songNumber].getFileName()), 0, 30);
    ofSetColor(255);
    font.drawString("Progress: " + to_string(progress * 100) + "%", 0, 45);
    font.drawString("Volume: " + to_string(sound.getVolume()) + "%", 0, 75);
    font.drawString("Loop: " + shownLoopStatus  + "   Repeat: " + shownRepeatStatus + "    Shuffle: " + shownShuffleStatus, 0, 60);
    font.drawString("Press H for help", currentWidth - strlen("Press H for help")*6, 15);
    font.drawString("< or > Swap Mode", currentWidth - strlen("< or > SWAP MODE")*7, 30);
    ofSetColor(255, 255, 0);
    //Draw Drop Down Menus
    font.drawString("Up Next: " + nextSong, 0, 90);
    font.drawString("My Music: ", currentWidth - strlen("My Music: ")*6, 90);
    font.drawString("PWD: " + directoryPath, 0, 180);
    font.drawString("FPS: " + to_string((int) ofGetFrameRate()), 0, 195);
}




void ofApp::drawProgressBar(float pos)
{
    ofFill();
    ofSetColor(255);
    ofDrawRectangle(0, ofGetHeight() - 10, ofGetWidth() * pos, 20);
}

void ofApp::drawUpNext(){
    ofSetColor(255);
    // don't itterate out of bounds of the vector

    for (int i = 0; i < 5; i++){
        ofSetColor(255);
  
        if (songNumber + i  < songVectorSize){
            if (songNumber + i == songNumber){
                ofSetColor(255, 255, 0);
            }
            font.drawString("    " + to_string(songNumber+i) + " " + songVector[songNumber + i].getFileName(), 
            0, 105+(i*12));
        }
        else{
            return;
        }
       // font.drawString("    " + to_string(songNumber+i) + " " + songVector[songNumber + i + songListDisplacement].getFileName(), 
        //0, 105+(i*12));
    }
}

void ofApp::drawSetSongNumber(){
    ofSetColor(255);
    font.drawString("Enter the song number in the vector you want to play", ofGetWidth() / 2 - 100, ofGetHeight() / 2);
    font.drawString("Press enter to confirm", ofGetWidth() / 2 - 100, ofGetHeight() / 2 + 15);
    font.drawString("Press '/' to cancel" , ofGetWidth() / 2 - 100, ofGetHeight() / 2 + 30);
    font.drawString("Current Song Number: " + to_string(songNumber), ofGetWidth() / 2 - 100, ofGetHeight() / 2 + 45);
    font.drawString(songNumberString, ofGetWidth() / 2 - 100, ofGetHeight() / 2 + 60);
}



void ofApp::showCollection(){
    ofSetColor(255);
    int currentWidth = ofGetWidth();
    for (int i = 0; i < songVectorSize/10; i++)
    {
        if (songListDisplacement + i + songNumber > songVectorSize){
            return;
        }
        font.drawString(to_string(songNumber + i + songListDisplacement) + " " + songVector[songNumber + i + songListDisplacement].getFileName(), currentWidth - 500, 105+(i*15));
    }
}



void ofApp::drawUserPrompt()
{
    // draw an empty text box to get the directory of the song 
    ofSetColor(255, 255, 255);
    font.drawString("Press tab to select the music directory or enter the directory of the song", ofGetWidth() / 2 - 225, ofGetHeight() / 2);
    font.drawString("Press enter to confirm", ofGetWidth() / 2 - 100, ofGetHeight() / 2 + 20);
    ofSetColor(255,0,0);
    font.drawString(directoryPath, ofGetWidth() / 2 - 100, ofGetHeight() / 2 + 40);

}