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
		void setAmplitude();

	private:
		std::string modeArray[3] = {"Rectangle Height Visualizer", "Circle Radius Visualizer", "Rectangle Width Visualizer"};
		bool outputingUserAudio = false;
		int songNumber = 0;
		ofSoundPlayer sound;
		AudioVisualizer visualizer;
		bool loopStatus = false; 
		bool helpStatus = false;
		int color = ofRandom(255);
		bool playing = false;
		int mode = 0;
		std::string songArray[6] = {"iReallyWannaStayAtYourHouse.mp3","OliverTreeMissyou.flac","newSongShadowOnTheSun.flac","makeThisRight.mp3", "somethingMemorable.mp3", "beHereNowHybrid.mp3"};
		int songArraySize = (sizeof(songArray)/sizeof(songArray[0]))-1;
		int cur_x, cur_y = 0;
		float sound_length;
		float shownAmplitude; 
		int decay = 0; // 0 = no decay, 1 = decay
		float progress = 0;
		float lastPos = 0;
		bool repeatStatus = false;
		bool barPause = false;
		vector<float> amplitudes;
		vector<float> lastAmplitudes; 
		int priorScreenHeight = ofGetHeight();
		float heightRatio = 1;
		
		
		
};
