#pragma once

#include "ofMain.h"
#include "AudioVisualizer.h"
#include <math.h>

class ofApp : public ofBaseApp
{
public:
	void setup();
	void update();
	void draw();

	void drawMode1(vector<float> amplitudes);
	void drawMode2(vector<float> amplitudes);
	void drawMode3(vector<float> amplitudes);
	void drawMode4(vector<float> amplitudes);
	void drawMode5();
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

private:
	ofSoundPlayer sound;
	AudioVisualizer visualizer;
	double volume_level = 1.0;
	bool playing = false;
	char mode = '1';
	int colors[3] = {ceil(ofRandom(255)), ceil(ofRandom(255)), ceil(ofRandom(255))};
	string songname = "";
	double position = sound.getPositionMS();
	int rotatebypi64th = 0;
	int key_list[256];
	bool r_pressed = false;
	int key_position = 0;
	bool t_pressed = false; 
	string in_file;
	string temp_str;
	string inputs; 
	bool has4secondselapsed = true;
	int loop_position = 0;
	float current_time = ofGetElapsedTimeMillis();
	string replaying = "";
	int t_pressed_counter = 0;
};
