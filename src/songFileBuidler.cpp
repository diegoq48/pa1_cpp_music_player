#include "ofApp.h"
#include <regex>

void ofApp::songFileBuilder(){
    ofFile songFile;
    if(!songFile.exists()){
        songFile.create("songs.txt");
        ofLog(OF_LOG_NOTICE, "File created");
        songFile.open("songs.txt", ofFile::WriteOnly);
        ofLog(OF_LOG_NOTICE, "File opened");
        for (int i = 0; i < songVectorSize; i++){
            ofLog(OF_LOG_NOTICE, "Writing to file" + songVector[i].getFileName());
            songFile << (songVector[i].getFileName()) << endl;
        }
        songFile.close();
        ofLog(OF_LOG_NOTICE, "File closed");
    }
    else{
        ofLog(OF_LOG_NOTICE, "File already exists");
        ofLog(OF_LOG_NOTICE, "Removing file");
        songFile.remove("songs.txt");
        songFileBuilder();
    }
/*     else{
        ofFile file("songs.txt");
        file.remove();
    } */
/*     else{
        ofFile file("songs.txt");
        file.open(ofFile::ReadOnly);
        std::string line;
        while (getline(file, line)){
            songVector.push_back(line);
        }
    } */

    
}



// Black Magic with regex  works now 
void ofApp::songSearch(std::string searchParameter){
    ofFile songFile; 
    //std::transform(searchParameter.begin(), searchParameter.end(), searchParameter.begin(), ::tolower);
    songFile.open("songs.txt", ofFile::ReadOnly);
    ofLog(OF_LOG_NOTICE, "File opened");
    ofLog(OF_LOG_NOTICE, "Searching for " + searchParameter);
    std::regex regex(searchParameter, std::regex_constants::icase);
    for (int i = 0; i < songVectorSize; i++){
        std::string line;
        while (getline(songFile, line)){
            
            if (std::regex_search(line, regex)){
                ofLog(OF_LOG_NOTICE, "Match found" + line);
                searchMatches.push_back(i);
            }
        }
    }
    ofLog(OF_LOG_NOTICE, "File closed");
    songFile.close();
    for (auto it = searchMatches.begin(); it != searchMatches.end(); it++){
        ofLog(OF_LOG_NOTICE, "Match found at " + *it);
    }
    return;

    
}
