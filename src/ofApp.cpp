#include "ofApp.h"
#include <ctime>









// switch the gets called whenever a key is pressed 
void ofApp::keyPressed(int key)
{
    if (gettingDirectory){
        switch(key){
            case(OF_KEY_RETURN):
                gettingDirectory = false;
                break;
            case(OF_KEY_BACKSPACE):
                directoryPath = directoryPath.substr(0, directoryPath.length()-1);
                break;
            case(OF_KEY_LEFT_SHIFT):
                break;
            default:
                directoryPath += key;
                break;
        } 
        return;
    }
    if (setSongNumberStatus){
        switch(key){
            case('/'):
                setSongNumberStatus = false;
                break;
            case(OF_KEY_BACKSPACE):
                songNumberString = songNumberString.substr(0, songNumberString.length()-1);
                break;
            case(OF_KEY_LEFT_SHIFT):
                break;
            case OF_KEY_RETURN:
                sound.unload();
                songNumber = stoi(songNumberString);
                if (songNumber >= songVectorSize  || songNumber < 0){
                    songNumber = 0;
                }
                playing = true;
                sound.load(songVector[songNumber]);
                sound.play();
                songNumberString = "";
                setSongNumberStatus = false;
                break;
            default:
                if (isdigit(key)){
                    songNumberString += key;
                }
                break;
        } 
        return;
    }
    switch (key){
    // play/pause key 
    case 'p':
        if (playing)
        {
            lastPos = progress;
            sound.stop();
            playing = !playing;
            break;
        }

        sound.setPosition(lastPos);
        sound.play();
        playing = !playing;
        break;
    
    // mode changes 
    case '1':
        mode = 1; break;
    case '2':
        mode = 2; break;
    case '3':
        mode = 3; break;
    case '4':
        mode = 4; break;
    case 'a':
        barPause = !barPause; break;
    // playes the next song 
    case 'd':
        playing = true;
        ofApp::changeSong(1);
        break;
    // increases volume 
    case '=':
        if (sound.getVolume() < 2.0)
        {
            sound.setVolume(sound.getVolume() + 0.1);
        }
        break;
    // lowers Volume 
    case '-':
        if (sound.getVolume() > 0.0)
        {
            sound.setVolume(sound.getVolume() - 0.1);
        }
        break;
    // plays random song
    case 'b':
        sound.unload();
        srand(time(NULL));
        sound.load(songVector[rand() % songVectorSize]);
        break;
    // plays the same song over and over again
    case 'r':
        repeatStatus = !repeatStatus;
        sound.setLoop(repeatStatus);
        break;
    // sets variable that allow array to start at zero once it has reached the end 
    case 'l':
        loopStatus = !loopStatus; break;
    // tells draw to print the hOF_KEY_SUPERelp menu
    case 'h':
        helpStatus = !helpStatus; break;
    // fullscreen
    case 'f':
        ofToggleFullscreen(); break;
    //plays the previous song if shuffle status is off 
    case 'z':
        if(!shuffleStatus){
            playing = true; 
            ofApp::changeSong(-1);
        }
        break;
    case OF_KEY_RIGHT:
        sound.setPosition(sound.getPosition() + 0.005);
        break;
    case OF_KEY_LEFT:
        sound.setPosition(sound.getPosition() - 0.005);
        break;
    case OF_KEY_DOWN:

        songListDisplacement++;
        
        break;
    case OF_KEY_UP:

        songListDisplacement--;
        break;
    case 's' :
        shuffleStatus = !shuffleStatus;
        if(!shuffleStatus){break;}
        ofApp::changeSong(0); break;
    case 'k':
        sound.stop();
        sound.unload();
        songVector.clear();
        songVectorSize = 0;
        gettingDirectory = true;
        directoryPath = "";
        break;
    case '/':
        
        setSongNumberStatus = !setSongNumberStatus;
    case '<':
        if (mode == 4)
        {
            mode = 1;
            break;
        }
        mode++;
        
        break;
    case '>':
        if (mode == 1)
        {
            mode = 4;
            break;
        }
        mode--;
        break;
    case 't':
        statusSaver();
        OF_EXIT_APP(0);
        break;
    default:
        break;
    }
    return;
}

void ofApp::keyReleased(int key)
{
}

void ofApp::mouseMoved(int x, int y)
{
    if (x < 50 && y < 90 && y >75)
    {
        hoveringUpNext = true;
    }
    else
    {
        hoveringUpNext = false;
    }
    if( x > ofGetWidth() - 50 && y < 90 && y >75)
    {
        hoveringMyMusic = true;
    }
    else
    {
        hoveringMyMusic = false;
    }
    
}

void ofApp::mouseDragged(int x, int y, int button)
{
    if (y >= ofGetHeight() - 10 && button == 0)
    {
        float posf = (float)x / (float)ofGetWidth();
        sound.setPosition(posf);
    }
}

void ofApp::mousePressed(int x, int y, int button)
{
    if (y >= ofGetHeight() - 10 && button == 0)
    {
        float posf = (float)x / (float)ofGetWidth();
        sound.setPosition(posf);
    }
    if (x < 50 && y < 90 && y >75)
    {
        drawingSongs = !drawingSongs;
    }
    if( x > ofGetWidth() - 50 && y < 90 && y >75)
    {
        drawingCollection  = !drawingCollection;
    }
}

void ofApp::mouseReleased(int x, int y, int button)
{
}

void ofApp::mouseEntered(int x, int y)
{
}

void ofApp::mouseExited(int x, int y)
{
}

void ofApp::windowResized(int w, int h)
{
    heightRatio = ofGetHeight() / priorScreenHeight;
    priorScreenHeight = ofGetHeight();
}

void ofApp::gotMessage(ofMessage msg)
{
}

void ofApp::dragEvent(ofDragInfo dragInfo)
{
}


void ofApp::setup()
{
    sound.setLoop(false);
    sound.setVolume(2);
    font.load("sans-serif.ttf", 12);
    ofSetBackgroundColor(00, 00, 00);
    ofSetWindowTitle("Music Player");
}


void ofApp::update()
{
    ofSoundUpdate();
    visualizer.updateAmplitudes();
    progress = sound.getPosition();
    if (progress > 0.99 && !repeatStatus)
    {
        ofApp::changeSong(1);
    }
    if(!gettingDirectory && songVectorSize == 0){
        getSongDirectory();
    }
}

void ofApp::draw()
{
    if (setSongNumberStatus)
    {
        ofApp::drawSetSongNumber();
        return;
    }
    if(gettingDirectory)
    {
        ofApp::drawUserPrompt();
        return;
    }
    if (songListing)
    {
        ofApp::drawUpNext();
    }
    if(hoveringUpNext){
        ofDrawRectangle(0, 75, 50, 15);
    }
    if(hoveringMyMusic){
        ofDrawRectangle(ofGetWidth() - 50, 75, 50, 15);
    }
    if (drawingCollection)
    {
        ofApp::showCollection();
    }

    if (ofGetHeight() > 199 && ofGetWidth() > 199)
    {
        ofSetColor(255);
        float pos = playing ? progress : lastPos;
        if (!playing && !helpStatus)
        {
            font.drawString("Press 'P' to play some music!", (ofGetWidth() / 2) - strlen("Press 'p' to play some music!")*8, ofGetHeight() / 2);
        }
        ofApp::setAmplitude();
        switch (mode)
        {
        case 1:
            ofApp::drawMode1(amplitudes);
            break;
        case 2:
            ofApp::drawMode2(amplitudes);
            break;
        case 3:
            ofApp::drawMode3(amplitudes);
            break;
        case 4:
            ofApp::drawMode4(amplitudes);
            break;
        default:
            break;
        }
        if (helpStatus)
        {
            ofApp::drawHelp();
        }
        ofApp::drawHud(); 
        ofApp::drawProgressBar(pos);
        if(drawingSongs){
            drawUpNext();
        }
        
        return; 
    }
    
    ofSetColor(255);
    font.drawString("Please resize your window", (ofGetWidth() / 2) - strlen("Please resize your window")*8, ofGetHeight() / 2);
}
