#include "ofApp.h"


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



void ofApp::changeSong(int displacement)
{
    sound.unload();
    songNumber += displacement;
    if (shuffleStatus)
    {
        srand(time(NULL));
        songNumber = rand() % songVectorSize;
        sound.load(songVector[songNumber]);
        sound.play();
        playing = true; 
        return;
    }
    if (songNumber >= songVectorSize || songNumber < 0)
    {
        songNumber = 0;
        if (loopStatus){
            sound.load(songVector[songNumber]);
            sound.play();
            playing = true; 
            return;
        }
        playing = false;
        sound.load(songVector[songNumber]);
        return; 
    }
    ofLog(OF_LOG_NOTICE, "Song number: " + ofToString(songNumber));
    sound.load(songVector[songNumber]);
    sound.play();
    ofLog(OF_LOG_NOTICE, "Song loaded: " + songVector[songNumber].getFileName());
}


void ofApp::getSongs(ofDirectory dir)
{
    ofLog(OF_LOG_NOTICE, "Getting songs, exploring directory: " + dir.getAbsolutePath());
	dir.listDir();
	for(auto file : dir)
	{
		if(file.isDirectory())
		{
            ofLog(OF_LOG_NOTICE, "Directory found: " + file.getAbsolutePath() + " exploring... recursivly");
			getSongs(ofDirectory(file.getAbsolutePath()));
		}
		else
		{
            string ext = file.getExtension();
            if (ext == "mp3" || ext == "wav" || ext == "ogg" || ext == "flac" || ext == "aiff" || ext == "m4a")
            {
                ofLog(OF_LOG_NOTICE, "File found: " + file.getAbsolutePath());
			    songVector.push_back(file);
            }
		}
	}
}

void ofApp::getSongDirectory()
{
    ofDirectory dir(directoryPath);
    if (!dir.exists()){
        ofLog(OF_LOG_ERROR, "Directory does not exist");
        gettingDirectory = true;
        return;
    }
    getSongs(dir);
    songVectorSize = songVector.size();
    ofLog(OF_LOG_NOTICE, "Song vector size: " + ofToString(songVectorSize));
    if (songVectorSize == 0){
        ofLog(OF_LOG_ERROR, "No songs found");
        gettingDirectory = true;
        return;
    }
    sound.load(songVector[songNumber]);
    songFileBuilder(); 
}

void ofApp::getDirectory()
{
    ofFileDialogResult result = ofSystemLoadDialog("Select a directory", true);
    if (result.bSuccess)
    {
        directoryPath = result.getPath();
        ofLog(OF_LOG_NOTICE, "Directory path: " + directoryPath);
        gettingDirectory = false;
        getSongDirectory();
    }
    else
    {
        ofLog(OF_LOG_ERROR, "User cancelled the dialog");
        gettingDirectory = true;
    }
}

void ofApp::statusSaver(){
    return; 
}