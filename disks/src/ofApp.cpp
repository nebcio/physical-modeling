#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
	gui.setup();
	gui.add(mesh.setup("mesh", false));
	gui.add(G.setup("G", 0.5, 0.01, 75));
	gui.add(frameRate.setup("Frame Rate", 30, 1, 120));
	gui.add(dt.setup("dt", 0.5, 0.001, 1));
	gui.add(centerMass.setup("Center Mass", 500, 100, 1'000));
	gui.add(centerX.setup("Center X", 499, 15, 985));
	gui.add(centerY.setup("Center Y", 499, 15, 985));

	mesh.addListener(this, &ofApp::onMeshChange);
	centerMass.addListener(this, &ofApp::onMassChange);
	frameRate.addListener(this, &ofApp::onFrameRateChange);
	centerX.addListener(this, &ofApp::onCenterXChange);
	centerY.addListener(this, &ofApp::onCenterYChange);

	center = Disk(centerMass, 15.0f, centerX, centerY, 0.0f, 0.0f, ofColor(253, 218, 13));	//

	// generate disks on mesh
	for (int x = 10; x < windowW; x += 40) {	
		for (int y = 10; y < windowH; y += 25) {
			disks.emplace_back(ofRandomuf() * 20.0f, ofRandomuf() * 5.0f, x, y, (ofRandomuf() - 0.5f) * 2.0f, (ofRandomuf() - 0.5f) * 2.0f, ofColor(ofRandom(220) + 30, ofRandom(220) + 30, ofRandom(220) + 30));
		}
	}

	for (int x = 0; x < windowW; ++x) {
		std::vector<float> viscosity = { 0.0005, 0.0, 0.0005 };
		std::vector<float> column;

		for (int y = 0; y < windowW; ++y) {
			if (y < 400) column.push_back(viscosity.at(0));
			else if (y < 600) column.push_back(viscosity.at(1));
			else column.push_back(viscosity.at(2));
		}
		fluids.push_back(column);
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	for (auto& disk : disks) {
		disk.avoidCollision(windowW, windowH);
	}
	for (auto& disk : disks) {
		disk.attraction(center, disks, G, dt);
		disk.calcDrag(&fluids, dt);
		disk.calcVelocity(dt);
		disk.move(dt);
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
void ofApp::mousePressed(int x, int y, int button){

}

void ofApp::onMeshChange(bool& mesh)
{
	disks.clear();
	if (mesh) {
		for (int x = 10; x < windowW; x += 40) {	// generate disks on mesh
			for (int y = 10; y < windowH; y += 25) {
				disks.emplace_back(ofRandomuf() * 20.0f, ofRandomuf() * 5.0f, x, y, (ofRandomuf() - 0.5f) * 2.0f, (ofRandomuf() - 0.5f) * 2.0f, ofColor(ofRandom(220) + 30, ofRandom(220) + 30, ofRandom(220) + 30));
			}
		}
	}
	else {
		for (int i = 0; i < N; ++i) {
			disks.emplace_back(ofRandomuf() * 20.0f, ofRandomuf() * 5.0f, ofRandom(990) + 10, ofRandom(990) + 10, (ofRandomuf() - 0.5f) * 2.0f, (ofRandomuf() - 0.5f) * 2.0f, ofColor(ofRandom(220) + 30, ofRandom(220) + 30, ofRandom(220) + 30));
		}
	}
}

void ofApp::onMassChange(float &mass)
{
	center.mass = mass;
}

void ofApp::onFrameRateChange(int& rate)
{
	ofSetFrameRate(rate);
}

void ofApp::onCenterXChange(int& x)
{
	center.pos.x = x;
}

void ofApp::onCenterYChange(int& y)
{
	center.pos.y = y;
}
