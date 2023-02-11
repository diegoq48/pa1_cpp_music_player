#pragma once

#include "ofMain.h"
#include "AudioVisualizer.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();

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
		void changeSong();

	private:
		int songNumber = 0;
		ofSoundPlayer sound;
		AudioVisualizer visualizer;
		int color = ofRandom(254);
		bool playing = false;
		char mode = '1';
		std::string songArray[5] = {"iReallyWannaStayAtYourHouse.mp3","OliverTreeMissyou.flac","newSongShadowOnTheSun.flac","makeThisRight.mp3", "somethingMemorable.mp3"};
		int songArraySize = (sizeof(songArray)/sizeof(songArray[0]))-1;
		int cur_x, cur_y = 0;
		float sound_length;
		int decay = 0; // 0 = no decay, 1 = decay
		float progress = 0;
		float lastPos = 0;
};
