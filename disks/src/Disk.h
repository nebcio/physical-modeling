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
		/* direction_vec * G *M / r^3 */
		float sqDistance = pos.squareDistance(otherDisk.pos);

		ofVec2f a_tmp = (otherDisk.pos - pos) * G * otherDisk.mass / (sqDistance * otherDisk.pos.distance(pos));
		return a_tmp;
	}

	void avoidCollision(int borderX, int borderY) {
		/* to avoid collison with borders or walls and slow down object */
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
		/* to calculate atraction with other objects */
		a = ofVec2f(0.0f, 0.0f);
		if ((pos - center.pos).lengthSquared() > (r + center.r) * (r + center.r))
			a = calcA(center, G);

		for (auto& otherDisk : otherDisks) {
			if (pos != otherDisk.pos) {
				a += calcA(otherDisk);
			}
		}	
	}

	void calcDrag(float dt = 0.01f) {
		/* to calculate drag: F= -6*PI*v*r*viscosity; F=ma; v=v+a*dt */
		ofVec2f drag = -6 * PI * vel * r * getViscosity(pos);
		vel += (drag / mass * dt);
	}

	float getViscosity(ofVec2f position) {
		if (position.y < 400) return 0.01f;
		else if (position.y < 600) return 0.0f;
		else return 0.0005f;

	}

	void calcVelocity(float dt = 0.1f) {
		/* to calculate velocity; limited to size of window */
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

