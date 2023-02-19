#pragma once

#include "ofMain.h"
#include "AudioVisualizer.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();

		void drawMode0(vector<float> amplitudes);
		void drawMode1(vector<float> amplitudes);
		void drawMode2(vector<float> amplitudes);
		void drawMode3(vector<float> amplitudes);
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
		void changeSong(int displacement);
		void drawHud();
		void drawProgressBar(float pos);
		void drawHelp();
		void setup3D(bool doSetup);
		void setupLighting(ofLight& light, bool doSetup);
		void setAmplitude();
		void getSongs(ofDirectory dir);
		void drawSongs();
		int songSearch(string songName);

	private:
		std::string modeArray[4] = {"Rectangle Height Visualizer", "Circle Radius Visualizer", "Rectangle Width Visualizer", "3D Voxel Visualizer"};
		int songNumber = 0;
		ofSoundPlayer sound;
		AudioVisualizer visualizer;
		bool loopStatus = false; 
		bool helpStatus = false;
		int color = ofRandom(255);
		bool playing = false;
		int mode = 0;
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
		vector<float> amplitudes;
		vector<float> lastAmplitudes; 
		int priorScreenHeight = ofGetHeight();
		float heightRatio = 1;
		bool songListing = false;
		bool shuffleStatus = false;

		
		
};
