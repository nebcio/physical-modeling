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
		/* direction_vec * G *M / r^2 */
		float sqDistance = pos.squareDistance(otherDisk.pos);

		ofVec2f a_tmp = (otherDisk.pos - pos) * G * otherDisk.mass / sqDistance;
		return a_tmp;
	}

	void avoidCollision(int borderX, int borderY) {
		/* to avoid collison with borders or walls */
		if (pos.x - r < 0 || pos.x + r > borderX) {
			vel.x = -vel.x * 0.9;
			if (pos.x - r < 0) pos.x = r;
			else pos.x = borderX - r;
		}
		if (pos.y - r < 0 || pos.y + r > borderY) {
			vel.y = -vel.y * 0.9;
			if (pos.y - r < 0) pos.y = r;
			else pos.y = borderY - r;
		}
	}

	void attraction(Disk& center, std::vector<Disk>& otherDisks,float G = 0.1, float dt = 1.0f) {

		a = ofVec2f(0.0f, 0.0f);
		if ((pos - center.pos).lengthSquared() > (r + center.r) * (r + center.r))
			a = calcA(center, G);

		for (auto& otherDisk : otherDisks) {
			if (pos != otherDisk.pos) {
				a += calcA(otherDisk);
			}
		}	
	}

	void calcDrag(std::vector<std::vector<float>>* fluids, float dt = 0.01f) {
		ofVec2f drag = -6 * PI * vel * r * fluids->at(pos.x).at(pos.y);
		vel += (drag / mass * dt);
	}

	void calcVelocity(float dt = 0.1f) {
		vel += dt * a;
		if (vel.x > 1000.0f) vel.x = 1000.0f;
		else if (vel.x < -1000.0f) vel.x = -1000.0f;

		if (vel.y > 1000.0f) vel.y = 1000.0f;
		else if (vel.y < -1000.0f) vel.y = -1000.0f;
	}

	void move(float dt = 0.1f) {
		pos += dt * vel;
	}
};

