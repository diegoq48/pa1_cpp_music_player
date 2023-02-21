#include "ofApp.h"
#include <ctime>



void ofApp::drawMode1(vector<float> amplitudes)
{
    ofFill();
    ofSetColor(00, 00, color);


    for (int i = 32; i >= 0; i--)
    {
        shownAmplitude = (amplitudes[32 - (i + 1)] * 10 * heightRatio);
        if (fabs(amplitudes[32 - (i + 1)] * 10) > ofGetHeight() - 20)
        {
            shownAmplitude = ((ofGetHeight() - 20) * -1);
        }
        ofDrawRectRounded(ofGetWidth() / 64 * i, ofGetHeight() +10, ofGetWidth() / 64, shownAmplitude, 5);
    }


    for (int i = 32; i < 64; i++)
    {
        shownAmplitude = (amplitudes[i - 32] * 10 * heightRatio);
        if (fabs(amplitudes[i - 32] * 10) > ofGetHeight() - 20)
        {
            shownAmplitude = (ofGetHeight() - 20) * -1;
        }
        ofDrawRectRounded(ofGetWidth() / 64 * i, ofGetHeight()+10, ofGetWidth() / 64, shownAmplitude, 5);
    }
}




void ofApp::drawMode2(vector<float> amplitudes)
{
    ofSetLineWidth(5);
    ofNoFill();
    ofSetColor(color, 00, 00);
    int bands = amplitudes.size();
    for (int i = 0; i < bands; i++)
    {
        shownAmplitude = amplitudes[i] * 10 * heightRatio;
        if (amplitudes[i] *10 * heightRatio > visualizerWindowHeight / 2)
        {
            shownAmplitude = (visualizerWindowHeight / 2);
        }
        ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, shownAmplitude * 10 * heightRatio);
    }
}




void ofApp::drawMode3(vector<float> amplitudes)
{
    ofSetColor(00, color, 00);
    ofFill();
    for (int i = 64; i > 0; i--)
    {
        shownAmplitude = amplitudes[i] * -10 * heightRatio;
        if (amplitudes[i] * -10 * heightRatio > ofGetWidth() / 2){
            shownAmplitude = (ofGetWidth() / 2) -10;
            }
        
        ofDrawRectangle(0, (ofGetHeight() - (20 * i)), shownAmplitude, ofGetHeight() / 64);
    }
    for (int i = 64; i > 0; i--)
    {
        shownAmplitude = amplitudes[i] * -10 * heightRatio;
        if (amplitudes[i] * -10 * heightRatio > ofGetWidth() / 2){
            shownAmplitude = (ofGetWidth() / 2)-10;
        }

        ofDrawRectangle(ofGetWidth(), (ofGetHeight() - (20 * i)), shownAmplitude * -1, ofGetHeight() / 64);
    }
}

void ofApp::setup3D(bool doSetup){
    if (doSetup) {
        // Setup the lighting
        setupLighting(light1, true);
        setupLighting(light2, true);

        // Setup the camera
        cam.setPosition(0, 900, 1000);
        cam.lookAt(glm::vec3(0, 700, 500));
        cam.begin();

        // Setup the lights for even lighting across the scene
        light1.setPosition(0, 500, 1500);
        light2.setPosition(0, 500, -1500);
        light1.draw();
        light2.draw();

        // Setup the scene
        ofPushStyle();
        ofPushMatrix();
        ofRotateDeg(90, 0, 0, 1); // Rotate the whole scene 90 degrees around the z axis to align the boxes vertically
        ofRotateDeg(ofGetElapsedTimef()*50, 0.5, 0, 0); // Rotate the whole scene around the x axis to make it spin

        ofEnableLighting();
        light1.enable();
        light2.enable();
    } else {
        setupLighting(light1, false);
        setupLighting(light2, false);
        ofPopMatrix();
        ofPopStyle();
        cam.end();
    }

};



void ofApp::drawMode4(vector<float> amplitudes){
    setup3D(true);
    ofSetColor(0, 0, color);
    for (int i = 0; i < 64; i++){
        if (amplitudes[i] < 0){
            // Draws a voxel-like circle for each amplitude
            ofDrawBox(ofPoint(20*i,0,0),20, amplitudes[i] * 8 , amplitudes[i] * 4);
            ofDrawBox(ofPoint(20*i,0,0),20, amplitudes[i] * 6 , amplitudes[i] * 6);
            ofDrawBox(ofPoint(20*i,0,0),20, amplitudes[i] * 4 , amplitudes[i] * 8);
        }
    }
    setup3D(false);
}



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
    font.drawString("Up Next: " + songVector[songNumber + 1].getFileName(), 0, 90);
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
 



void ofApp::drawProgressBar(float pos)
{
    ofFill();
    ofSetColor(255);
    ofDrawRectangle(0, ofGetHeight() - 10, ofGetWidth() * pos, 20);
}



void ofApp::setAmplitude()
{
    if (!barPause)
    {
        lastAmplitudes = amplitudes;
        amplitudes = visualizer.getAmplitudes();
        return;
    }
    amplitudes = lastAmplitudes;
}

void ofApp::drawSongs(){
    ofSetColor(255);
    for (int i = 0; i < 5; i++){
        ofSetColor(255);
        if (i == 0){
            ofSetColor(255, 255, 0);
        }
        font.drawString("    " + to_string(songSearch(songVector[songNumber+i].getFileName())) + " " + songVector[songNumber + i + songListDisplacement].getFileName(), 
        0, 105+(i*12));
    }
}


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


void ofApp::keyPressed(int key)
{
    switch (key){
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
    case 'd':
        playing = true;
        ofApp::changeSong(1);
        break;
    case '=':
        if ((sound.getVolume() == 2.0))
        {
            break;
        }
        sound.setVolume(sound.getVolume() + 0.1);
        break;
    case '-':
        if ((sound.getVolume() == 0.0))
        {
            break;
        }
        sound.setVolume(sound.getVolume() - 0.1);
        break;
    case 'b':
        sound.unload();
        srand(time(NULL));
        sound.load(songVector[rand() % songVectorSize]);
        break;
    case 'r':
        repeatStatus = !repeatStatus;
        sound.setLoop(repeatStatus);
        break;
    case 'l':
        loopStatus = !loopStatus; break;
    case 'h':
        helpStatus = !helpStatus; break;
    case 'f':
        ofToggleFullscreen(); break;
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
        if (songListDisplacement != 0)
        {
            songListDisplacement++;
        }
        break;
    case OF_KEY_UP:
        if (songListDisplacement != 0)
        {
            songListDisplacement--;
        }
        break;
    case 's' :
        shuffleStatus = !shuffleStatus; ofApp::changeSong(0); break;
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
    if (x < 56 && y > 90 && y < 105)
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
    if (y > ofGetHeight()/2 -8 && y < ofGetHeight()/2 + 8)
    {
        drawing = !drawing;
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
    visualizerWindowHeight = ofGetHeight() - ofGetHeight()/4;
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

	dir.listDir();

	for(auto file : dir)
	{
		if(file.isDirectory())
		{
			getSongs(ofDirectory(file.getAbsolutePath()));
		}
		else
		{
            dir.allowExt("mp3"); dir.allowExt("wav"); dir.allowExt("ogg"); dir.allowExt("flac"); dir.allowExt("aiff"); dir.allowExt("m4a"); dir.allowExt("wma");
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
        ofApp::drawSongs();
        return;
    }
    if(hoveringMyMusic){
        ofDrawRectangle(0, 90, 56, 15);
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
            drawMode1(amplitudes);
            break;
        case 2:
            drawMode2(amplitudes);
            break;
        case 3:
            drawMode3(amplitudes);
            break;
        case 4:
            drawMode4(amplitudes);
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
        if(drawing){
            drawSongs();
        }
        return; 
    }
    
    ofSetColor(255);
    font.drawString("Please resize your window", (ofGetWidth() / 2) - strlen("Please resize your window")*8, ofGetHeight() / 2);
}
