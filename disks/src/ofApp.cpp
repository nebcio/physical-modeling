#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	center = Disk(1000'000'000.0f, 15.0f, static_cast<int>(windowW / 2), static_cast<int>(windowH / 2), 0.0f, 0.0f, ofColor(253, 218, 13));	//

	for (int x = 0; x < windowW; x += 100) {	// generate disks on mesh
		for (int y = 0; y < windowH; y += 100) {
			disks.emplace_back(ofRandomuf() * 10.0f, ofRandomuf() * 10.0f, x, y, (ofRandomuf() - 0.5f) * 50.0f, (ofRandomuf() - 0.5f) * 50.0f, ofColor(ofRandom(220) + 30, ofRandom(220) + 30, ofRandom(220) + 30));
		}
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	for (auto& disk : disks) {
		disk.avoidCollision(windowW, windowH);
		disk.move();
		disk.centerA(center, G);
		disk.recalcA(disks, G);
		disk.calcV();
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(center.color);
	ofDrawCircle(center.pos, center.r);
	for (auto& disk : disks) {
			ofSetColor(disk.color);
			ofDrawCircle(disk.pos, disk.r);
	}
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
