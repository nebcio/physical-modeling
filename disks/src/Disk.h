#pragma once

#include "ofColor.h"

class Disk
{
public:
	ofVec2f pos;
	ofVec2f vel;
	ofVec2f a;
	ofColor color;
	float mass = 1.0f;
	float r = 1.0f;

	Disk() {
		color = ofColor(200, 200, 200);
		pos = ofVec2f(0.0f, 0.0f);
		vel = ofVec2f(1.0f, 1.0f);
	}

	Disk(float m, float r, int x, int y, float vx, float vy, ofColor c = ofColor(200, 200, 200)) {
		color = c;
		mass = m;
		this->r = r;
		pos.x = x;
		pos.y = y;
		vel.x = vx;
		vel.y = vy;
		a = ofVec2f(0.0f, 0.0f);
	}

	ofVec2f calcA(Disk& otherDisk, float G = 0.1, float dt = 1.0f) {
		/* direction_vec * -G *M / r^2 */
		float sqDistance = pos.squareDistance(otherDisk.pos);
		sqDistance = sqDistance < 1 ? 1: sqDistance > 1000 ? 1000 : sqDistance;

		ofVec2f a_tmp = (pos - otherDisk.pos) * G * otherDisk.mass / sqDistance;
		return a_tmp;
	}

	void centerA(Disk &centerDisk, float G = 0.1, float dt = 1.0f) {
		/* to calculate acceleration in time (dt) with center */
		a = ofVec2f(0.0f, 0.0f);
		if (pos != centerDisk.pos)
			a = calcA(centerDisk, G);
	}

	void recalcA(std::vector<Disk>& otherDisks, float G = 0.1, float dt = 1.0f) {
		/* to calculate acceleration in time (dt) with other disks */
		for (auto& otherDisk : otherDisks) {
			if (pos != otherDisk.pos) {
				a += calcA(otherDisk);
			}
		}
	}

	void calcV(float dt = 1.0f) {
		/* to calculate velocity in time (dt) */
		vel += dt * a;
	}

	void move(float dt = 1.0f) {
		/* to change position in time (dt) */
		pos += dt * vel;
	}

	void avoidCollision(int borderX, int borderY) {
		/* to avoid collison with borders or walls */
		if (pos.x + vel.x < 0 || pos.x + vel.x > borderX) vel.x = -vel.x;
		if (pos.y + vel.y < 0 || pos.y + vel.y > borderY) vel.y = -vel.y;
	}
};

