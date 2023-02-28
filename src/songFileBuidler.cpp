#include "ofApp.h"

void ofApp::songFileBuilder(){
    ofFile songFile;
    if(!songFile.exists()){
        songFile.create("songs.txt");
        ofLog(OF_LOG_NOTICE, "File created");
        songFile.open("songs.txt", ofFile::WriteOnly);
        ofLog(OF_LOG_NOTICE, "File opened");
        for (int i = 0; i < songVectorSize; i++){
            ofLog(OF_LOG_NOTICE, "Writing to file" + songVector[i].getFileName());
            songFile << songVector[i].getFileName() << endl;
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




void ofApp::songSearch(){
    
    return;

    
}
