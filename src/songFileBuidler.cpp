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



//Implement in the future with .json when playlist are added 
void ofApp::statusSaver(){

    ofFile statusFile(".statusFile.txt", ofFile::WriteOnly);
    if (statusFile.exists()){
        statusFile.remove();
    }
    statusFile.create(".statusFile.txt");
    statusFile.open(".statusFile.txt", ofFile::WriteOnly);
    statusFile << loopStatus << endl;
    statusFile << helpStatus << endl;
    statusFile << repeatStatus << endl;
    statusFile << shuffleStatus << endl;
    statusFile << mode << endl;
    statusFile << progress << endl;
    statusFile << songNumber << endl;
    statusFile << songVectorSize << endl;
    statusFile << directoryPath << endl;
    // Don't Uncomment statusFile << currentPlaylist << endl;
    statusFile.close();
    return; 
}


void ofApp::statusSetup(){
    ofFile statusFile(".statusFile.txt", ofFile::ReadOnly);
    if (statusFile.exists()){
        statusFile.open(".statusFile.txt", ofFile::ReadOnly);
        std::string line;
        int i = 0;
        while (getline(statusFile, line)){
            switch (i)
            {
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
                progress = stof(line);
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
    }
    return;    
}
