#include "ofApp.h"
#include <ctime>
// default file provided by open frameworks rtfm open frameworks to find out what every function does @https://openframeworks.cc/documentation/application/

 
void ofApp::keyPressed(int key)
{
    // called if user is adding to or selecting a playlist
    // track number is the value the user is hovering over
    if (selectingPlaylist || queueingPlaylist){
        ofLog(OF_LOG_NOTICE, "Selecting Playlist");
        switch(key){
            case(OF_KEY_RETURN):
                if (queueingPlaylist){
                    queueingPlaylist = false;
                    playlistSelector(playlistName);
                    break;
                }
                playlistDirectory.open("playlists");
                playlistDirectory.listDir();
                playlistName = playlistDirectory.getName(trackNumber);
                selectingPlaylist = false;
                searching = true;
                fillingPlaylist = true;
                break;
            case '.':
                selectingPlaylist = false;
                queueingPlaylist = false; 
            case '\'':
                queueingPlaylist = false;
                break;
            case OF_KEY_UP:
                if (trackNumber == 0){
                    trackNumber = playlistDirectory.size() - 1;
                    break;
                }
                trackNumber--;
                break;
            case OF_KEY_DOWN:
                if (trackNumber > (int)playlistDirectory.size() - 2){
                    trackNumber = 0;
                    break;
                }
                trackNumber++;
                break;
            default:
                break;
            
        } 
        ofLog(OF_LOG_NOTICE, "Playlist Name " + playlistName);
        return;
    }


    if (makingPlaylist){
        ofLog(OF_LOG_NOTICE, "Making Playlist");
        switch(key){
            case(OF_KEY_RETURN):
                if (playlistName != ""){
                    playlistBuilder(playlistName);
                    playlistName = "";
                    makingPlaylist = false;
                }
                break;
            case(OF_KEY_BACKSPACE):
                playlistName = playlistName.substr(0, playlistName.length()-1);
                break;
            case(OF_KEY_LEFT_SHIFT):
                break;
            case ',': 
                makingPlaylist = false;
                break;
            default:
                // Ignore weird keys that show up when shift is pressed
                if (key != 1 && key != 3680) {
                    playlistName += key;
                }
                break;
        } 
        ofLog(OF_LOG_NOTICE, "Playlist Name " + playlistName);
        return;
    }

    // allows the user to specify the directory from which to pull variables from 
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
            case(OF_KEY_TAB):
                getDirectory();
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

    // redirects user input for the searching function 
    if (searching){
        ofLog(OF_LOG_NOTICE, "Searching");
        if(key == '(' || key == ')' || key == '[' || key == ']' || key == '{' || key == '}'){
            return;
        }
        switch(key){
            case(OF_KEY_RETURN):
            // if the string is empy break since itll add the entire song file 
                if (searchString == ""){
                    break;
                }
                if (fillingPlaylist){
                    playlistPopulator(playlistName, songVector[searchMatches[trackNumber]].getAbsolutePath());
                    searchString = "";
                    searchMatches.clear();
                    break;
                }
                if (searchMatches.size() > 0){
                    sound.unload();
                    songNumber = searchMatches[trackNumber];
                    playing = true;
                    sound.load(songVector[songNumber]);
                    sound.play();
                    searchString = "";
                    searching = false;
                }
                break;
            case OF_KEY_UP:
                if (trackNumber == 0){
                    trackNumber = searchMatches.size() - 1;
                    break;
                }
                trackNumber--;
                break;
            case OF_KEY_DOWN:
                if (trackNumber == (int)searchMatches.size() -1){
                    trackNumber = 0;
                    break;
                }
                trackNumber++;
                break;
            case(OF_KEY_BACKSPACE):
                searchString = searchString.substr(0, searchString.length()-1);
                searchMatches.clear();
                trackNumber = 0;
                songSearch(searchString);
                break;
            case(OF_KEY_LEFT_SHIFT):
                break;
            case '?':
                searchString = "";
                searching = false;
                fillingPlaylist = false;
                break;
            default:
                // Ignore weird keys that show up when shift is pressed
                if (key != 1 && key != 3680) {
                    searchString += key;
                }
                searchMatches.clear();
                songSearch(searchString);
                trackNumber = 0;
                break;
        } 
        ofLog(OF_LOG_NOTICE, "Search String " + searchString);
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

        sound.setPosition(lastPos);//========================================================================

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
        ofApp::changeSong(1);
        break;


    // increases volume 
    case '=':
        if (sound.getVolume() <= 1.0)
        {
            ofLog(OF_LOG_NOTICE, "Volume = " + to_string(sound.getVolume()));
            sound.setVolume(sound.getVolume() + 0.1);
        }
        break;


    // lowers Volume 
    case '-':
        if (sound.getVolume() > 0.1)
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
//========================================================================


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
        }
        songListDisplacement < (int) songVectorSize - songNumber ? songListDisplacement++ : songListDisplacement = songVectorSize - songNumber;
        ofLog(OF_LOG_NOTICE, "Song List Displacement = " + to_string(songListDisplacement));
        break;

    // decreases songListDisplacement by 1 
    case OF_KEY_UP:
        if (!drawingCollection)
        {
            break;
        }
        ofLog(OF_LOG_NOTICE, "Song List Displacement = " + to_string(songListDisplacement));
        songListDisplacement > 0 - songNumber ? songListDisplacement-- : songListDisplacement = 0 - songNumber;
        break;
    
    // toggles shuffle on and off
    case 's' :
        shuffleStatus = !shuffleStatus;
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
    // enables searching
    case '?':
        searching = true;
        shuffleStatus = false;
        searchMatches.clear();
        break;
    // toggles filling rectangles excluding mode 3
    case ';':
        fillingRect = !fillingRect;
        break;
    //exit key 
    case 'q':
        statusSaver();
        ofLog(OF_LOG_NOTICE, "Status Saved");
        ofLog(OF_LOG_NOTICE, "Exiting...");
        OF_EXIT_APP(0);
        break;
    case 'm':
    // toggles mute 
        muted = !muted;
        muted? sound.setVolume(0) : sound.setVolume(0.5);
        break;
    // default case
    case ',':
        helpStatus = false;
        errorMessage = "";
        makingPlaylist = true;
        playlistName = "";
        break;
    case '.':
        trackNumber = 0;
        helpStatus = false;
        errorMessage = "";
        selectingPlaylist = true;
        fillingPlaylist = true;
        break;
    case '\'':
        helpStatus = false;
        errorMessage = "";
        queueingPlaylist = true;
        break;
    case 'o':
        sound.stop();
        sound.unload();
        songVector.clear();
        ofApp::getDirectory();
        break;
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
    // checks if mouse is hovering over the my music button
    if( x > ofGetWidth() - 50 && y < 90 && y >75)
    {
        hoveringMyMusic = true;
        return;
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
}//========================================================================

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
    statusSetup();
    ofLog(OF_LOG_NOTICE, "Starting Setup");
    font.load("sans-serif.ttf", 12);
    ofLog(OF_LOG_NOTICE, "loaded Font");
    ofSetBackgroundColor(00, 00, 00);
    ofSetWindowTitle("Music Player");
    sound.setVolume(0.5);
    sound.unload();
    color < 50? color += 50 : color = color;
    if(!gettingDirectory){sound.load(songVector[songNumber]);}
    ofLog(OF_LOG_NOTICE, "Finished Setup");
    
}


void ofApp::update()
{
    // if its not possible to play music and the user isnt getting music then get music 
    if(!gettingDirectory && 0 == songVectorSize && !queueingPlaylist){getSongDirectory();}
    // uppdates soundplayer 
    ofSoundUpdate();

    // updates variables 
    visualizer.updateAmplitudes();
    progress = sound.getPosition();
    pos = playing ? progress : lastPos;
    fillingRect? ofFill(): ofNoFill();
    ofApp::setAmplitude();

    // changes song automatically if the song is over and repeat is off 
    if (progress > 0.99 && !repeatStatus)
    {
        ofApp::changeSong(1);
        
    }
}

void ofApp::draw()
{
    // if user is getting directory, draw user prompt and return 
    if(gettingDirectory)
    {
        ofApp::drawUserPrompt();
        return;
    }

    // switch to determine which mode to draw
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

    // constants for drawing
    ofApp::drawHud();
    ofApp::drawProgressBar(pos);

    // verfies boolean variables and draws their respective prompts
    if (helpStatus){ofApp::drawHelp();}
    
    if (setSongNumberStatus){ ofApp::drawSetSongNumber(); return;}

    if (hoveringMyMusic){ ofNoFill(); ofDrawRectangle(ofGetWidth() - 70, 75, 70, 15);}

    if (drawingCollection){ ofApp::showCollection();}

    if (searching){ ofApp::drawSearchPrompt();}

    if (makingPlaylist){ ofApp::drawPlaylistPrompt();}

    if (selectingPlaylist){ ofApp::drawAvailablePlaylists();}

    if (queueingPlaylist){ofApp::drawAvailablePlaylists();}

    return;
}

