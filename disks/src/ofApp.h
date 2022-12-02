#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Disk.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		
		ofxPanel gui;
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

		// opor aerodynamiczny (formula stokesa dla niskich liczb reynoldsa

		
};
