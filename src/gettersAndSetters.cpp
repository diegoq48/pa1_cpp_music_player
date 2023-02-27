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
    
    sound.load(songVector[songNumber]);
    sound.play();
    
}


void ofApp::getSongs(ofDirectory dir)
{
    dir.allowExt("mp3"); dir.allowExt("wav"); dir.allowExt("ogg"); dir.allowExt("flac"); dir.allowExt("aiff"); dir.allowExt("m4a"); dir.allowExt("");

	dir.listDir();
	for(auto file : dir)
	{
		if(file.isDirectory())
		{
			getSongs(ofDirectory(file.getAbsolutePath()));
		}
		else
		{
            if (file.getExtension() == ""){
                continue;
            }
			songVector.push_back(file);

		}
	}
}

void ofApp::getSongDirectory()
{
    ofDirectory dir(directoryPath);
    std::cout << dir.getAbsolutePath() << std::endl;
    if (!dir.exists()){
        std::cout << "Directory does not exist" << std::endl;
        gettingDirectory = true;
        return;
    }
    getSongs(dir);
    songVectorSize = songVector.size();
    sound.load(songVector[0]);
    songFileBuilder(); 
}

void ofApp::statusSaver(){
    return; 
}