#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "particleSystem.h"
#include "generator.h"
#include "updater.h"
#include "emitter.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void mousePressed(int x, int y, int button);
		void windowResized(int w, int h);


		int maxNumParticles = 10000;

		ofEasyCam cam;
		ofLight light;

		ofxPanel gui;
		ofxIntSlider numParticle;
		ofxFloatSlider dt;

		ofImage brickImage;
		ofImage backgroundImage;
		ofTexture brickTexture;
		ofTexture backgroundTexture;

		ofBoxPrimitive ground;
		ofBoxPrimitive floor;
		ofSpherePrimitive background;

		std::vector<ParticleSystem> particleSystems;

};
