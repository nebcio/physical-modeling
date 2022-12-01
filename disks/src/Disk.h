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

		ofVec2f a_tmp = (pos - otherDisk.pos) * G * otherDisk.mass / sqDistance;
		return a_tmp;
	}

	void avoidCollision(int borderX, int borderY) {
		/* to avoid collison with borders or walls */
		if (pos.x - r < 0 || pos.x + r + vel.x > borderX) {
			vel.x = -vel.x;
			if (pos.x - r < 0) pos.x = r;
			else pos.x = borderX - r;
		}
		if (pos.y - r < 0 || pos.y + r > borderY) {
			vel.y = -vel.y;
			if (pos.y - r < 0) pos.y = r;
			else pos.y = borderY - r;
		}
	}

	void attraction(Disk& center, std::vector<Disk>& otherDisks, float G = 0.1, float dt = 1.0f) {
		pos += dt * vel;

		a = ofVec2f(0.0f, 0.0f);
		if ((pos - center.pos).lengthSquared() > (r + center.r) * (r + center.r))
			a = calcA(center, G);

		for (auto& otherDisk : otherDisks) {
			if (pos != otherDisk.pos) {
				a += calcA(otherDisk);
			}
		}

		vel += dt * a;
	}
};

