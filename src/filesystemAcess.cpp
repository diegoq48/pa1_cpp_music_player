// This file contains any and all files that acess the host filesystem 
#include "ofApp.h"
#include <regex>


// tries to use a operating system dialog to get the directory path (only works on windows) if not reverts to a text input 
void ofApp::getDirectory()
{
    ofFileDialogResult result = ofSystemLoadDialog("Select a directory", true);
    if (result.bSuccess) {
        directoryPath = result.getPath();
        ofLog(OF_LOG_NOTICE, "Directory path: " + directoryPath);
        gettingDirectory = false;
        getSongDirectory();
    } else {
        ofLog(OF_LOG_ERROR, "User cancelled the dialog");
        gettingDirectory = true;
    }
    return;
}

// adds songs to the specified playlist 
void ofApp::playlistPopulator(std::string playlistName, std::string songPath)
{
    ofFile playlistFile;
    ofLog(OF_LOG_NOTICE, "Playlist name: " + playlistName);
    playlistFile.open("playlists/" + playlistName, ofFile::Append);
    ofLog(OF_LOG_NOTICE, "Opened playlist file: " + playlistName);
    playlistFile << songPath << std::endl;
    ofLog(OF_LOG_NOTICE, "Wrote song path: " + songPath);
    playlistFile.close();
    return;
}

// playlist builder creates the text file for the playlist under ./data/playlists 
void ofApp::playlistBuilder(std::string playlistName)
{
    ofFile playlistFile;
    ofDirectory playlistDir("playlists");
    if (!playlistDir.exists()) {
        playlistDir.create();
    }
    playlistFile.create("playlists/" + playlistName + ".txt");
    return;
}

// loads the playlist into the song vector
void ofApp::playlistSelector(std::string playlistName)
{
    ofFile playlistFile;
    ofLog(OF_LOG_NOTICE, "Playlist name: " + playlistName);
    playlistFile.open("playlists/" + playlistName, ofFile::ReadOnly);
    ofLog(OF_LOG_NOTICE, playlistFile.getAbsolutePath());
    sound.unload();
    songVector.clear();
    std::string line;
    ofLog(OF_LOG_NOTICE, "Loading playlist: " + playlistFile.getAbsolutePath());
    while (getline(playlistFile, line)) {
        ofLog(OF_LOG_NOTICE, "Adding song: " + line);
        songVector.push_back(ofFile(line));
    }
    // resets the user mutable variables
    songNumber = 0;
    setPlaybackMode(0);
    playing = false; 
    songVectorSize = songVector.size();
    sound.load(songVector[0]);
    playlistFile.close();
    return;
}

// gets songs out of a directory and its subdirectories 
void ofApp::getSongs(ofDirectory dir)
{
    ofLog(OF_LOG_NOTICE, "Getting songs, exploring directory: " + dir.getAbsolutePath());
	dir.listDir();
	for(auto file : dir) {
        // recursive call if the file is a directory
		if(file.isDirectory()) {
			getSongs(ofDirectory(file.getAbsolutePath()));
		} else {
            // made for compatibility with windows and linux gets audio file extensions and adds them to the vector
            string ext = file.getExtension();
            if (ext == "mp3" || ext == "wav" || ext == "ogg" || ext == "flac" || ext == "aiff" || ext == "m4a") {
                ofLog(OF_LOG_NOTICE, "File found: " + file.getAbsolutePath());
			    songVector.push_back(file);
            }
		}
	}
}

// gets the songs from the directory path
void ofApp::getSongDirectory()
{
    ofDirectory dir(directoryPath);
    // checks if file exists 
    if (!dir.exists()) {
        ofLog(OF_LOG_ERROR, "Directory does not exist");
        errorMessage = "Directory does not exist";
        gettingDirectory = true;
        return;
    }
    getSongs(dir);
    errorMessage = "Sucess, getting songs";
    songVectorSize = songVector.size();
    ofLog(OF_LOG_NOTICE, "Song vector size: " + ofToString(songVectorSize));
    if (songVectorSize == 0) {
        ofLog(OF_LOG_ERROR, "No songs found");
        gettingDirectory = true;
        errorMessage = "No songs found";
        return;
    }
    sound.load(songVector[songNumber]);
    songFileBuilder(); 
    return;
}

// Saves the current state of the program using a status file saved in data folder  
void ofApp::statusSaver()
{
    ofFile statusFile(".statusFile.txt", ofFile::WriteOnly);
    if (statusFile.exists()) {
        statusFile.remove();
    }
    statusFile.create(".statusFile.txt");
    statusFile.open(".statusFile.txt", ofFile::WriteOnly);
    statusFile << loopStatus << endl;
    statusFile << helpStatus << endl;
    statusFile << repeatStatus << endl;
    statusFile << shuffleStatus << endl;
    statusFile << mode << endl;
    statusFile << pos << endl;
    statusFile << songNumber << endl;
    statusFile << songVectorSize << endl;
    statusFile << directoryPath << endl;
    statusFile.close();
    return; 
}

// Loads the status file and sets the program to the last state
void ofApp::statusSetup()
{
    ofFile statusFile(".statusFile.txt", ofFile::ReadOnly);
    ofLog(OF_LOG_NOTICE, "Status file exists: " + to_string(statusFile.exists()));
    if (statusFile.exists()) {
        statusFile.open(".statusFile.txt", ofFile::ReadOnly);
        std::string line;
        int i = 0;
        while (getline(statusFile, line)) {
            switch (i) {
                case 0:
                    loopStatus = (line == "1");
                    break;
                case 1:
                    helpStatus = (line == "1");
                    break;
                case 2:
                    repeatStatus = (line == "1");
                    break;
                case 3:
                    shuffleStatus = (line == "1");
                    break;
                case 4:
                    mode = stoi(line);
                    break;
                case 5:
                    pos = stof(line);
                    break;
                case 6:
                    songNumber = stoi(line);
                    break;
                case 7:
                    songVectorSize = stoi(line);
                    break;
                case 8:
                    directoryPath = line;
                    break;
                default:
                    break;
            }
            i++;
        }
        statusFile.close();
        gettingDirectory = false;
        getSongs(ofDirectory(directoryPath));
    } else {
        ofLog(OF_LOG_NOTICE, "Status file does not exist");
        gettingDirectory = true;
    }
    return;
}

// Search Function using regex uses a songfile stored in data folder 
void ofApp::songSearch(std::string searchParameter)
{
    ofFile songFile; 
    songFile.open("songs.txt", ofFile::ReadOnly);
    if (!songFile.exists()) {
        ofLog(OF_LOG_ERROR, "File does not exist");
        songFileBuilder();
    }
    ofLog(OF_LOG_NOTICE, "File opened");
    ofLog(OF_LOG_NOTICE, "Searching for " + searchParameter);
    std::regex regex(searchParameter, std::regex_constants::icase);
    int count = 0;
        std::string line;
        while (getline(songFile, line)) {
            if (std::regex_search(line, regex)) {
                ofLog(OF_LOG_NOTICE, "Match found" + line);
                searchMatches.push_back(count);
            }
        count++;
        }
    ofLog(OF_LOG_NOTICE, "File closed");
    songFile.close();
   
    for (int i=0;i  < (int)searchMatches.size(); i++) {
        ofLog(OF_LOG_NOTICE, "Match found at " + to_string(searchMatches[i]));
    }       
    return;
}

// creates a song file after checking if it already exists if it does exists it deletes it and does a recursive call
void ofApp::songFileBuilder()
{
    ofFile songFile;
    if(!songFile.exists()) {
        songFile.create("songs.txt");
        ofLog(OF_LOG_NOTICE, "File created");
        songFile.open("songs.txt", ofFile::WriteOnly);
        ofLog(OF_LOG_NOTICE, "File opened");
        for (int i = 0; i < songVectorSize; i++) {
            ofLog(OF_LOG_NOTICE, "Writing to file" + songVector[i].getFileName());
            songFile << (songVector[i].getFileName()) << endl;
        }
        songFile.close();
        ofLog(OF_LOG_NOTICE, "File closed");
    } else {
        ofLog(OF_LOG_NOTICE, "File already exists");
        ofLog(OF_LOG_NOTICE, "Removing file");
        songFile.remove("songs.txt");
        songFileBuilder();
    }
    return;
    
}

//resets to the user provided directory path 
void ofApp::resetPlaylist(std::string directoryPath)
{
    songVector.clear();
    ofApp::getSongDirectory();
    return;
}