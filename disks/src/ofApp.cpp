#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
	gui.setup();
	gui.add(G.setup("G", 0.5, 0.01, 75));
	gui.add(frameRate.setup("Frame Rate", 30, 1, 120));
	gui.add(dt.setup("dt", 0.5, 0.001, 1));
	gui.add(centerMass.setup("Center Mass", 500, 100, 1'000));
	gui.add(centerX.setup("Center X", 499, 15, 1000));
	gui.add(centerY.setup("Center Y", 499, 15, 1000));

	center = Disk(centerMass, 15.0f, centerX, centerY, 0.0f, 0.0f, ofColor(253, 218, 13));	//

	for (int x = 20; x < windowW; x += 100) {	// generate disks on mesh
		for (int y = 20; y < windowH; y += 400) {
			disks.emplace_back(ofRandomuf() * 20.0f, ofRandomuf() * 10.0f, x, y, (ofRandomuf() - 0.5f) * 2.0f, (ofRandomuf() - 0.5f) * 2.0f, ofColor(ofRandom(220) + 30, ofRandom(220) + 30, ofRandom(220) + 30));
		}
	}

	for (int x = 0; x < windowW; ++x) {
		std::vector<float> viscosity = { -0.05, 0.0, 0.05 };
		std::vector<float> column;
		for (int y = 0; y < windowW; ++y) {
			if (y < 300) column.push_back(viscosity.at(0));
			else if (y < 600) column.push_back(viscosity.at(1));
			else column.push_back(viscosity.at(2));
		}
		fluids.push_back(column);
	}

}

//--------------------------------------------------------------
void ofApp::update(){
	ofSetFrameRate(frameRate);
	center.mass = centerMass;
	center.pos.x = centerX;
	center.pos.y = centerY;
	for (auto& disk : disks) {
		disk.attraction(center, disks, fluids, G, dt);
		disk.avoidCollision(windowW, windowH);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetBackgroundColor(ofColor::black);
	ofSetColor(center.color);
	ofDrawCircle(center.pos, center.r);
	for (auto& disk : disks) {
			ofSetColor(disk.color);
			ofDrawCircle(disk.pos, disk.r);
	}
	gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}
