#include "ofApp.h"
#include <ctime>


// switch the gets called whenever a key is pressed 
void ofApp::keyPressed(int key)
{
    // chekcs the getting direcory boolean in order to determin whether to direct all input into the direcotry path string
    if (gettingDirectory){
        ofLog(OF_LOG_NOTICE, "Getting Directory");
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
                // Ignore weird keys that show up when shift is pressed
                if (key != 1 && key != 3680) {
                    directoryPath += key;
                }
                break;
        } 
        ofLog(OF_LOG_NOTICE, "Directory path " + directoryPath);
        return;
    }




    // checks the set song number boolean in order to determin whether to direct all input into the song number string
    if (setSongNumberStatus){
        ofLog(OF_LOG_NOTICE, "Setting Song Number");
        switch(key){
            case('/'):
                songNumberString = "";
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
        ofLog(OF_LOG_NOTICE, "Song Number =" + songNumberString);
        return;
    }



    // default case if no booleans are true 
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
        mode = 1; ofLog(OF_LOG_NOTICE, "Mode = 1"); break;
    case '2':
        mode = 2; ofLog(OF_LOG_NOTICE, "Mode = 2"); break;
    case '3':
        mode = 3; ofLog(OF_LOG_NOTICE, "Mode = 3"); break;
    case '4':
        mode = 4; ofLog(OF_LOG_NOTICE, "Mode = 4"); break;
    case 'a':
        ofLog(OF_LOG_NOTICE, "bar Puased");
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
            ofLog(OF_LOG_NOTICE, "Volume = " + to_string(sound.getVolume()));
            sound.setVolume(sound.getVolume() + 0.1);
        }
        break;


    // lowers Volume 
    case '-':
        if (sound.getVolume() > 0.0)
        {
            ofLog(OF_LOG_NOTICE, "Volume = " + to_string(sound.getVolume()));
            sound.setVolume(sound.getVolume() - 0.1);
        }
        break;


    // plays random song
    case 'b':
        sound.unload();
        srand(time(NULL));
        songNumber = rand() % songVectorSize;
        ofLog(OF_LOG_NOTICE, "Random Song Number = " + to_string(songNumber));
        sound.load(songVector[songNumber]);
        sound.play();
        break;


    // plays the same song over and over again
    case 'r':
        repeatStatus = !repeatStatus;
        ofLog(OF_LOG_NOTICE, "Repeat Status = " + to_string(repeatStatus));
        sound.setLoop(repeatStatus);
        break;


    // sets variable that allow array to start at zero once it has reached the end 
    case 'l':
        ofLog(OF_LOG_NOTICE, "Loop Status = " + to_string(loopStatus));
        loopStatus = !loopStatus; break;


    // tells ofdraw to print the help menu
    case 'h':
        ofLog(OF_LOG_NOTICE, "Help Status = " + to_string(helpStatus));
        helpStatus = !helpStatus; break;


    // fullscreen toggle
    case 'f':
        ofLog(OF_LOG_NOTICE, "Fullscreen toggled");
        ofToggleFullscreen(); break;

    // plays the previous song if shuffle is off
    case 'z':
        if(!shuffleStatus){
            playing = true; 
            ofApp::changeSong(-1);
        }
        break;

    // increases the song positon by 0.005 seconds    
    case OF_KEY_RIGHT:
        sound.setPosition(sound.getPosition() + 0.005);
        ofLog(OF_LOG_NOTICE, "Position = " + to_string(sound.getPosition()));
        break;

    // decreases the song positon by 0.005 seconds
    case OF_KEY_LEFT:
        sound.setPosition(sound.getPosition() - 0.005);
        ofLog(OF_LOG_NOTICE, "Position = " + to_string(sound.getPosition()));
        break;

    // increases songListDisplacement by 1
    case OF_KEY_DOWN:
        if (!drawingCollection)
        {
            break;
            ofLog(OF_LOG_WARNING, "Song List Displacement = " + to_string(songListDisplacement));
        }
        songListDisplacement++;
        ofLog(OF_LOG_NOTICE, "Song List Displacement = " + to_string(songListDisplacement));
        break;

    // decreases songListDisplacement by 1 
    case OF_KEY_UP:
        if (!drawingCollection)
        {
            break;
            ofLog(OF_LOG_WARNING, "Song List Displacement = " + to_string(songListDisplacement));
        }
        ofLog(OF_LOG_NOTICE, "Song List Displacement = " + to_string(songListDisplacement));
        songListDisplacement--;
        break;

    // toggles shuffle on and off
    case 's' :
        shuffleStatus = !shuffleStatus;
        drawingSongs = false;
        drawingCollection = false;
        ofLog(OF_LOG_NOTICE, "Shuffle Status = " + to_string(shuffleStatus));
        if(!shuffleStatus){break;}
        ofApp::changeSong(0); break;

    // changes song directory 
    case 'k':
        ofLog(OF_LOG_NOTICE, "changing song directory");
        sound.stop();
        sound.unload();
        songVector.clear();
        songVectorSize = 0;
        gettingDirectory = true;
        directoryPath = "";
        break;

    // allows user to set song number by toggling setSongNumberStatus
    case '/':
        setSongNumberStatus = !setSongNumberStatus;
        ofLog(OF_LOG_NOTICE, "Set Song Number Status = " + to_string(setSongNumberStatus));

    // changes modes 
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

    //exit key 
    case 't':
        statusSaver();
        ofLog(OF_LOG_NOTICE, "Status Saved");
        ofLog(OF_LOG_NOTICE, "Exiting...");
        OF_EXIT_APP(0);
        break;
    // default case
    default:
        ofLog(OF_LOG_WARNING, "Key not recognized");
        break;
    }
    return;
}

void ofApp::keyReleased(int key)
{
}

void ofApp::mouseMoved(int x, int y)
{
    // checks if mouse is hovering over the up next button
    if (x < 50 && y < 90 && y >75)
    {
        hoveringUpNext = true;
        return; 
    }
    hoveringUpNext = false;

    // checks if mouse is hovering over the my music button
    if( x > ofGetWidth() - 50 && y < 90 && y >75)
    {
        hoveringMyMusic = true;
    }
    hoveringMyMusic = false;
    
    
}

void ofApp::mouseDragged(int x, int y, int button)
{
    // tracks mouse to set the position of the song to the mouse position if mouse y < 10 
    if (y >= ofGetHeight() - 10 && button == 0)
    {
        float posf = (float)x / (float)ofGetWidth();
        sound.setPosition(posf);
    }
}

void ofApp::mousePressed(int x, int y, int button)
{
    // sets the position of the song to the mouse position if mouse y < 10
    if (y >= ofGetHeight() - 10 && button == 0)
    {
        float posf = (float)x / (float)ofGetWidth();
        sound.setPosition(posf);
    }
    // draw up next menu if mouse is clicked over the up next button  
    if (x < 50 && y < 90 && y >75)
    {
        drawingSongs = !drawingSongs;
    }
    // draw my music menu if mouse is clicked over the my music button
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
    // updates the height ratio when the window is resized
    heightRatio = ofGetHeight() / priorScreenHeight;
    priorScreenHeight = ofGetHeight();
    ofLog(OF_LOG_NOTICE, "Height Ratio = " + to_string(heightRatio));
    ofLog(OF_LOG_NOTICE, "Prior Screen Height = " + to_string(priorScreenHeight));
}

void ofApp::gotMessage(ofMessage msg)
{
}

void ofApp::dragEvent(ofDragInfo dragInfo)
{
}


void ofApp::setup()
{
    // sets framerate to something not cancerous like 30fps 
    // vertical sync is on to prevent screen tearing
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofSetCircleResolution(100);
    ofLog(OF_LOG_NOTICE, "Starting Setup");
    sound.setLoop(false);
    ofLog(OF_LOG_NOTICE, "set sound to not loop");
    sound.setVolume(2);
    ofLog(OF_LOG_NOTICE, "set sound to 2");
    font.load("sans-serif.ttf", 12);
    ofLog(OF_LOG_NOTICE, "loaded Font");
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
        
        return; 
    }
    
    ofSetColor(255);
    ofLog(OF_LOG_WARNING, "Drawing Error please resize");
    font.drawString("Please resize your window", (ofGetWidth() / 2) - strlen("Please resize your window")*8, ofGetHeight() / 2);
}
