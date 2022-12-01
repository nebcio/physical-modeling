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

	ofVec2f calcA(Disk& otherDisk, float G = 0.1, float dt = 0.0f) {
		/* -G*M*t / r^2 || -G*M*(p1-p2) / r^3 */
		ofVec2f a_tmp = -G * otherDisk.mass * ((pos - vel * dt) - pos) / (pos.distance(otherDisk.pos) * pos.distance(otherDisk.pos) * pos.distance(otherDisk.pos));
		return a_tmp;
	}

	void centerA(Disk &otherDisk, float G = 0.1) {
		/* to calculate acceleration in time (dt) with center */
		a = ofVec2f(0.0f, 0.0f);
		if (pos.distance(otherDisk.pos) > 0)
			a = calcA(otherDisk, G);
	}

	void recalcA(std::vector<Disk>& otherDisks, float G = 0.1) {
		/* to calculate acceleration in time (dt) with other disks */
		for (auto& otherDisk : otherDisks) {
			if (pos.distance(otherDisk.pos) != 0) {
				a = calcA(otherDisk);
				if (pos.distance(otherDisk.pos) < r + otherDisk.r)
					a *= -0.5;
			}
		}
	}

	void calcV(float dt = 0.01f) {
		/* to calculate velocity in time (dt) */
		vel += dt * a;
	}

	void move(float dt = 0.01f) {
		/* to change position in time (dt) */
		pos += dt * vel;
	}

	void avoidCollision(int borderX, int borderY) {
		/* to avoid collison with borders or walls */
		if (pos.x + r + vel.x < 0 || pos.x + r + vel.x > borderX) vel.x = -vel.x;
		if (pos.y + r + vel.y < 0 || pos.y + r + vel.y > borderY) vel.y = -vel.y;
	}
};

