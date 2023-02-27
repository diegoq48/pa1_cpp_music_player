#include "ofApp.h"

void ofApp::songFileBuilder(){
    ofFile songFile;
    if(!songFile.exists()){
        songFile.create("songs.txt");
        songFile.open("songs.txt", ofFile::WriteOnly);
        for (int i = 0; i < songVectorSize; i++){
            songFile << songVector[i].getFileName() << endl;
        }
        songFile.close();
    }
    else{
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
    
}
