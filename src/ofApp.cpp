#include "ofApp.h"
#include <ctime>

// First draw Mode Creates a visualizer that resembels a bar graph by grabing the first 32 amplitudes 
// and Mirroring them whilst also truncating values so that they dont exceed the height of the window 
// as well as multiplying them by a constant that is the ratio of the window height to the color is a 
// random shade of blue that is generated at the start of the program and is changed every time the
// program is run.



// Draws a help menu at the center of the screen with instructions on how to use the program
// substracts the length of the string from the center of the screen to center the text
void ofApp::drawHelp()
{
    ofSetColor(255);
    int helpMidScreenY = ofGetHeight() / 2 - 48;
    int helpMidScreenX = ofGetWidth() / 2;
    font.drawString("Press 'p' to play/pause", helpMidScreenX - strlen("Press 'p' to play/pause") / 2 * 8, (helpMidScreenY));
    font.drawString("Press '0' to switch to mode 0", helpMidScreenX - strlen("Press '0' to switch to mode 0") / 2 * 8, helpMidScreenY + 15);
    font.drawString("Press '1' to switch to mode 1", helpMidScreenX - strlen("Press '1' to switch to mode 1") / 2 * 8, helpMidScreenY + 30);
    font.drawString("Press '2' to switch to mode 2", helpMidScreenX - strlen("Press '2' to switch to mode 2") / 2 * 8, helpMidScreenY + 45);
    font.drawString("Press '3' to switch to mode 3", helpMidScreenX - strlen("Press '3' to switch to mode 3") / 2 * 8, helpMidScreenY + 60);
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
}



// Draws the HUD at the top of the screen
// and draws the drop down menu selectors for the music collections
void ofApp::drawHud()
{
    std::string shownLoopStatus = loopStatus? "ON":"OFF";
    std::string shownRepeatStatus = repeatStatus? "ON":"OFF";
    std::string shownShuffleStatus = shuffleStatus? "ON":"OFF";
    ofSetColor(255);
    int currentWidth = ofGetWidth();
    font.drawString("Mode: " + modeArray[mode-1], 0, 15);
    ofSetColor(255,255,0);
    font.drawString("Now Playing: " + (songVector[songNumber].getFileName()), 0, 30);
    ofSetColor(255);
    font.drawString("Progress: " + to_string(progress * 100) + "%", 0, 45);
    font.drawString("Volume: " + to_string(sound.getVolume()) + "%", 0, 75);
    font.drawString("Loop: " + shownLoopStatus  + "   Repeat: " + shownRepeatStatus + "    Shuffle: " + shownShuffleStatus, 0, 60);
    font.drawString("Press H for help", currentWidth - strlen("Press H for help")*6, 15);
    font.drawString("< or > Swap Mode", currentWidth - strlen("< or > SWAP MODE")*7, 30);
    ofSetColor(255, 255, 0);
    //Draw Drop Down Menus
   // font.drawString("Up Next: " + songVector[songNumber + 1].getFileName(), 0, 90);
    font.drawString("My Music: ", currentWidth - strlen("My Music: ")*6, 90);
}




void ofApp::setupLighting(ofLight& light, bool doSetup){
    if (doSetup) {
        // Adjust the light for the most even lighting
        light.setDirectional();
        light.setSpotlight();
        light.setSpotlightCutOff(2000);
        light.setSpotConcentration(1);
        light.setPointLight();
        ofEnableDepthTest();
    } else {
        ofDisableLighting();
        ofDisableDepthTest();
        light.disable();
    }
}
 



// Draws a progress bar at the bottom of the screen by multiplying by the position of the song
void ofApp::drawProgressBar(float pos)
{
    ofFill();
    ofSetColor(255);
    ofDrawRectangle(0, ofGetHeight() - 10, ofGetWidth() * pos, 20);
}


// Gets the visualizer bars and sets them 
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


// Draws the next five songs on the array after songNumber
void ofApp::drawUpNext(){
    ofSetColor(255);
    for (int i = 0; i < 5; i++){
        ofSetColor(255);
        if (i == 0){
            ofSetColor(255, 0,0);
        }
        font.drawString("    " + to_string(songSearch(songVector[songNumber+i].getFileName())) + " " + songVector[songNumber + i + songListDisplacement].getFileName(), 
        0, 105+(i*12));
    }
}


void ofApp::showCollection(){
    ofSetColor(255);
    for (int i = 0; i < songVectorSize/(((ofGetHeight()-90)/12)); i++){
        ofSetColor(255);
        if (i == 0 && songListDisplacement == 0){
            ofSetColor(255, 0,0);
        }
        font.drawString(to_string(songSearch(songVector[songNumber+i].getFileName())) + " " + songVector[songNumber + i + songListDisplacement].getFileName(), ofGetWidth()-(songVector[songNumber+i].getFileName().length()*12)-5, 105+(i*12)+25);
    }
    return;
}



// Method to change songs unloads songs first in order to save space in memory and later checks all the boolean values for the modes in order 
// to determine what song to play 
void ofApp::changeSong(int displacement)
{
    sound.unload();
    songNumber = songNumber + displacement;
    if (shuffleStatus)
    {
        srand(time(NULL));
        songNumber = rand() % songVectorSize;
        sound.load(songVector[songNumber]);
        sound.play();
        playing = true; 
        return;
    }
    if ((songNumber > songVectorSize || songNumber < 0))
    {
        songNumber = 0;
        if(loopStatus){
            sound.load(songVector[songNumber]);
            sound.play();
            return; 
        }
        sound.stop();
        playing = false;
        sound.load(songVector[songNumber]);
        return;
    }
    sound.load(songVector[songNumber]);
    sound.play();
    
}

// removes spaces in a string

std::string spaceRemover(std::string word){
    std::string newWord = "";
    for (int i = 0; i < word.length(); i++){
        if (word[i] != ' '){
            newWord += word[i];
        }
    }
    return newWord;
}


// used to search for a song directly in the terminal not in gui 
int ofApp::songSearch(std::string songName){
    for (int i = 0; i < songVectorSize; i++) {
        if (songVector[i].getFileName() == songName) {
            return i; 
        }
    }
    ofLog() << "Song not found";
    font.drawString("Song not found", (ofGetWidth()/2)-112, ofGetHeight()/2);
    return -1;
}



// switch the gets called whenever a key is pressed 
void ofApp::keyPressed(int key)
{
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
        if ((sound.getVolume() != 2.0))
        {
            sound.setVolume(sound.getVolume() + 0.1);
        }
        break;
    // lowers Volume 
    case '-':
        if ((sound.getVolume() != 0.0))
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
    // tells draw to print the help menu
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
    case '/':
        //need to add a way to search for songs using a visual pop up and search function that needs to be optimized 
        break;
    default:
        break;
    }
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
    font.load("sans-serif.ttf", 11);
    image.load("background.jpg");
    ofSetBackgroundColor(00, 00, 00);
    ofSetWindowTitle("Music Player");
    ofDirectory dir("/home/diegoq/Music");
    getSongs(dir);
    songVectorSize = songVector.size();
    sound.load(songVector[0]);
}

void ofApp::getSongs(ofDirectory dir)
{
    dir.allowExt("mp3"); dir.allowExt("wav"); dir.allowExt("ogg"); dir.allowExt("flac"); dir.allowExt("aiff"); dir.allowExt("m4a"); dir.allowExt("");

	dir.listDir();
    std::cout << dir.getAbsolutePath() << std::endl;
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
void ofApp::update()
{
    ofSoundUpdate();
    visualizer.updateAmplitudes();
    progress = sound.getPosition();
    if (progress > 0.99 && !repeatStatus)
    {
        ofApp::changeSong(1);
    }
}

void ofApp::draw()
{
    image.draw(ofGetWidth()-250, ofGetHeight()-ofGetHeight()/4, 250, ofGetHeight()/4);
    if (songListing)
    {
        ofApp::drawUpNext();
        return;
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
        return;
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
