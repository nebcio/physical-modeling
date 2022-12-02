#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Disk.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void mousePressed(int x, int y, int button);
		
		void onMeshChange(bool& mesh);
		void onMassChange(float& mass);
		void onFrameRateChange(int& rate);
		void onCenterXChange(int& x);
		void onCenterYChange(int& y);

		ofxPanel gui;
		ofxToggle mesh;
		ofxFloatSlider G;
		ofxIntSlider frameRate;
		ofxFloatSlider dt;
		ofxFloatSlider centerMass;
		ofxIntSlider centerX;
		ofxIntSlider centerY;

		int N = 1000;
		int windowW = 1000, windowH = 1000;

		Disk center; 
		std::vector<Disk> disks;
		std::vector<std::vector<float>> fluids;

};
