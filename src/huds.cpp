#include "ofApp.h"


// this file contains all the text that is drawn on the screen 

// Draws help menu at the center of the screen
void ofApp::drawHelp()
{
    ofSetColor(255);
    int helpMidScreenY = ofGetHeight() / 2 - 48;
    int helpMidScreenX = ofGetWidth() / 2;
    font.drawString("Press ''' to start playing a playlist", helpMidScreenX - strlen("Press ''' to start playing a playlist") / 2 * 8, helpMidScreenY - 15);
    font.drawString("Press 'o' to go back to a stored directory", helpMidScreenX - strlen("Press 'o' to open a song") / 2 * 8, helpMidScreenY -30);
    font.drawString("Press ',' to create a playlist", helpMidScreenX - strlen("Press ',' to create a playlist") / 2 * 8, helpMidScreenY - 45);
    font.drawString("Press '.' to add a songs to a playlist", helpMidScreenX - strlen("Press '.' to add a song to a playlist") / 2 * 8, helpMidScreenY - 60);
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
    font.drawString("Press '?' to search for songs", helpMidScreenX - strlen("Press '?' to search for songs") / 2 * 8, helpMidScreenY + 285);
    font.drawString("Press 'm' to toggle mute", helpMidScreenX - strlen("Press 'm' to toggle mute") / 2 * 8, helpMidScreenY + 300);
    font.drawString("Press 'q' to exit the program", helpMidScreenX - strlen("Press 't' to exit the program") / 2 * 8, helpMidScreenY + 315);
    font.drawString("Press ';' to toggle filling bars", helpMidScreenX - strlen("Press ';' to toggle filling bars") / 2 * 8, helpMidScreenY + 330);
}

// Draws the main HUD at the top of the screen both right and left 
void ofApp::drawHud()
{
    std::string playbackoption = "None";
    if (loopStatus) {
        playbackoption = "Loop";
    } else if (repeatStatus) {
        playbackoption = "Repeat";
    } else if (shuffleStatus) {
        playbackoption = "Shuffle";
    }
    std::string shownLoopStatus = loopStatus? "ON":"OFF";
    std::string shownRepeatStatus = repeatStatus? "ON":"OFF";
    std::string shownShuffleStatus = shuffleStatus? "ON":"OFF";
    std::string isplaying = playing? "pause":"play";
    string nextSong = songNumber + 1 < songVectorSize? songVector[songNumber + 1].getFileName() : "No More Songs";
    ofSetColor(255);
    int currentWidth = ofGetWidth();
    font.drawString("Visual Mode: " + modeArray[mode-1], 0, 15);
    ofSetColor(255,255,0);
    font.drawString("Now Playing: " + (songVector[songNumber].getFileName()), 0, 30);
    ofSetColor(255);
    font.drawString("Progress: " + to_string((int)(pos * 100)) + "%", 0, 45);
    font.drawString("Volume: " + to_string((int)(sound.getVolume()*100)) + "%", 0, 75);
    font.drawString("Playback Mode: " + playbackoption, 0, 60);
    font.drawString("Press h for help", currentWidth - strlen("Press H for help")*6, 15);
    font.drawString("< or > Swap Mode", currentWidth - strlen("< or > SWAP MODE")*7, 30);
    ofSetColor(255, 255, 0);
    font.drawString("Up Next: " + nextSong, 0, 90);
    font.drawString("My Music: ", currentWidth - strlen("My Music: ")*6, 90);
    ofSetColor(255);
    font.drawString("PWD: " + directoryPath, 0, 105);
    font.drawString("FPS: " + to_string((int) ofGetFrameRate()), 0, 120);
    ofSetColor(255);
    font.drawString("Song Number: " + to_string(songNumber), 0, 135);
    font.drawString("Song Vector Size: " + to_string(songVectorSize), 0, 150);
    ofSetColor(255, 255, 0);
    font.drawString("Press 'p' to " + isplaying,0, 165);

}



// draws progress bar at the bottom of the screen
void ofApp::drawProgressBar(float pos)
{
    ofFill();
    ofSetColor(255);
    ofDrawRectangle(0, ofGetHeight() - 10, ofGetWidth() * pos, 20);
}


// Hud for when user is setting song number 
void ofApp::drawSetSongNumber(){
    ofSetColor(255);
    font.drawString("Enter the song number in the vector you want to play", ofGetWidth() / 2 - 100, ofGetHeight() / 2);
    font.drawString("Press enter to confirm", ofGetWidth() / 2 - 100, ofGetHeight() / 2 + 15);
    font.drawString("Press '/' to cancel" , ofGetWidth() / 2 - 100, ofGetHeight() / 2 + 30);
    font.drawString("Current Song Number: " + to_string(songNumber), ofGetWidth() / 2 - 100, ofGetHeight() / 2 + 45);
    font.drawString(songNumberString, ofGetWidth() / 2 - 100, ofGetHeight() / 2 + 60);
}



// drop down for show collection 
// arregle el show collection now it just stops when it crashes 
void ofApp::showCollection(){
    int currentWidth = ofGetWidth();
    for (int i = 0; i < 50; i++)
    {
        if (songListDisplacement + i + songNumber + 50 > songVectorSize || songListDisplacement + i + songNumber < 0 ){
            return;
        }
        songListDisplacement + i == 0 ? ofSetColor(255,255,0) : ofSetColor(255);
        font.drawString(to_string(songNumber + i + songListDisplacement) + " " + songVector[songNumber + i + songListDisplacement].getFileName(),
         currentWidth - 500, 105+(i*15));
    }
}



// Shown when user is resseting directory 
void ofApp::drawUserPrompt()
{
    ofSetColor(255, 255, 255);
    font.drawString("Press tab to select the music directory (Only on windows) or enter the directory of the song", ofGetWidth() / 2 - 225, ofGetHeight() / 2);
    font.drawString("Press enter to confirm", ofGetWidth() / 2 - 100, ofGetHeight() / 2 + 20);
    ofSetColor(255,0,0);
    font.drawString(directoryPath, ofGetWidth() / 2 - 100, ofGetHeight() / 2 + 40);
    font.drawString(errorMessage, ofGetWidth() / 2 - 100, ofGetHeight() / 2 + 60);
}


// Draws the search prompt at the center of the screen 
void ofApp::drawSearchPrompt(){
    ofSetColor(255, 255, 255);
    fillingPlaylist? font.drawString("Enter the name of the song you want to add", ofGetWidth() / 2 - 100, ofGetHeight() / 2) :  font.drawString("Enter the name of the song you want to play", ofGetWidth() / 2 - 100, ofGetHeight() / 2);
    font.drawString("Press enter to confirm", ofGetWidth() / 2 - 100, ofGetHeight() / 2 + 15);
    font.drawString("Press '?' to exit prompt" , ofGetWidth() / 2 - 100, ofGetHeight() / 2 + 30);
    font.drawString("Current Song Number: " + to_string(songNumber), ofGetWidth() / 2 - 100, ofGetHeight() / 2 + 45);
    font.drawString(searchString, ofGetWidth() / 2 - 100, ofGetHeight() / 2 + 60);
    font.drawString(errorMessage, ofGetWidth() / 2 - 100, ofGetHeight() / 2 + 75);

    for (int i = 0; i < (int)searchMatches.size() ; i++){
        if (i > 10){
            return;
        }
        i == trackNumber? ofSetColor(255, 255, 0) : ofSetColor(255);
        font.drawString(to_string(i) + " " + songVector[searchMatches[i]].getFileName(), ofGetWidth() / 2 - 100, ofGetHeight() / 2 + 90 + (i*15));
    }
}


// Draws the playlist prompt at the center of the screen to create a playlist
void ofApp::drawPlaylistPrompt(){
    ofSetColor(255, 255, 255);
    font.drawString("Enter the name of the playlist you want to create", ofGetWidth() / 2 - 100, ofGetHeight() / 2);
    font.drawString("Press enter to confirm", ofGetWidth() / 2 - 100, ofGetHeight() / 2 + 15);
    font.drawString(playlistName, ofGetWidth() / 2 - 100, ofGetHeight() / 2 + 60);
    font.drawString(errorMessage, ofGetWidth() / 2 - 100, ofGetHeight() / 2 + 75);
}


// shows the available playlists
void ofApp::drawAvailablePlaylists(){
    ofSetColor(255, 255, 255);
    fillingPlaylist? font.drawString("Enter the name of the playlist you want to populate to", ofGetWidth() / 2 - 100, ofGetHeight() / 2)
     : font.drawString("Enter the name of the playlist you want to play", ofGetWidth() / 2 - 100, ofGetHeight() / 2);
    font.drawString("Press enter to confirm", ofGetWidth() / 2 - 100, ofGetHeight() / 2 + 15);
    playlistDirectory.listDir("playlists");
    for (int i = 0; i < (int)playlistDirectory.size(); i++){
        i == trackNumber? ofSetColor(255, 255, 0) : ofSetColor(255);
        font.drawString(to_string(i) + " " + playlistDirectory.getName(i), ofGetWidth() / 2 - 100, ofGetHeight() / 2 + 90 + (i*15));
    }
}