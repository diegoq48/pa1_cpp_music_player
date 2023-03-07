// prepocessor directives
#pragma once

#include "ofMain.h"
#include "AudioVisualizer.h"
#include <ctime>
// object file for the audio visualizer

// class for the audio visualizer
class ofApp : public ofBaseApp{
	// public functions
	public:
		void setup();
		void update();
		void draw();
		void drawMode1(vector<float> amplitudes);
		void drawMode2(vector<float> amplitudes);
		void drawMode3(vector<float> amplitudes);
		void drawMode4(vector<float> amplitudes);
		void drawHelp();
		void drawHud();
		void drawPlaylistPrompt();
		void drawProgressBar(float pos);   
		void drawSearchPrompt();
		void drawSetSongNumber();
		void drawUpNext();
		void drawUserPrompt();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		void setPlaybackMode(char playbackMode);
		void changeSong(int displacement);
		void setRandomSong();
		void setupLighting(ofLight& light, bool doSetup);
		void setAmplitude();
		void getSongs(ofDirectory dir);
		void showCollection();

		void songFileBuilder();
		void songSearch(std::string searchParameter);
		void getSongDirectory();
		void getDirectory();
		
		void statusSaver();
		void statusSetup();

		void playlistBuilder(std::string playlistName);
		void playlistPopulator(std::string playlistName, std::string songPath);
		void playlistSelector(std::string playlistName);
		void drawAvailablePlaylists();
		void resetPlaylist(std::string directoryPath);


	// private vars for the audio visualizer
	private:
		void setup3D(bool doSetup);
		// array that holds name of modes for the visualizer
		std::string modeArray[4] = {"Rectangle Height Visualizer", "Circle Radius Visualizer", "Rectangle Width Visualizer", "3D Voxel Visualizer"};
		int songNumber = 0;
		ofSoundPlayer sound;
		AudioVisualizer visualizer;
		bool loopStatus = true; 
		bool helpStatus = false;
		int color = ofRandom(255);
		bool playing = false;
		int mode = 1;
		// main vector to hold the songs found in the filesystem should later be implemented with a linked list for better memory management || with a vector of pointers || as queued vectors 
		// very inefficient to have a vector of 1000+ songs in memory at once 
		vector<ofFile> songVector;
		int songVectorSize = 0;
		int cur_x, cur_y = 0;
		float sound_length;
		float shownAmplitude; 
		float progress = 0;
		float lastPos = 0;
		bool repeatStatus = false;
		ofLight light1;
		ofLight light2;
		ofEasyCam cam;
		bool barPause = false;
		// amplitudes that enable the visualizer to draw the shapes
		vector<float> amplitudes;
		vector<float> lastAmplitudes; 
		int priorScreenHeight = ofGetHeight();
		float heightRatio = 1;
		bool songListing = false;
		bool shuffleStatus = false;
		int songListDisplacement = 0; 
		ofTrueTypeFont font;
		bool hoveringMyMusic = false; 
		bool drawingCollection = false; 
		bool gettingDirectory = true;
		std::string directoryPath;
		bool setSongNumberStatus = false;
		std::string songNumberString;
		std::string errorMessage = "";
		// holds the position of the songs in the vector based on their position in the sound file 
		vector<int> searchMatches; 
		int songMatch;
		bool searching = false;
		std::string searchString = "";
		int trackNumber = 0; 
		bool fillingRect = true;
		bool muted = false;
		bool makingPlaylist = false; 
		bool fillingPlaylist = false;
		bool selectingPlaylist = false;
		bool queueingPlaylist = false;
		float pos;
		ofDirectory playlistDirectory = ofDirectory("playlists");
		std::string playlistName = "";



		
		
};
