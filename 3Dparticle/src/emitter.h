#pragma once

#include "ofMain.h"
#include "particleSystem.h"

class FireballEmitter : public Emitter
{
public:

    FireballEmitter(float emitRate, ofVec3f center, float radius) : Emitter(emitRate, center)
    {
        addGenerator(std::make_shared<SpherePositionGen>(center, radius));
        addGenerator(std::make_shared<ColorGen>(ofColor(255, 0, 0), ofColor(255, 255, 0)));
        addGenerator(std::make_shared<TimeGen>(1.0f, 6.0f));

        addGenerator(std::make_shared<VelocityGen>(ofVec3f(-5, 15, -5), ofVec3f(5, 30, 5)));
    }
};

class AshEmitter : public Emitter
{
public:

    AshEmitter(float emitRate, ofVec3f center, bool isGrayScale) : Emitter(emitRate, center)
    {
        addGenerator(std::make_shared<BoxPositionGen>(ofVec3f(-100, 150, -100), ofVec3f(100, 150, 100)));
        addGenerator(std::make_shared<ColorGen>(ofColor(100, 100, 100), ofColor(200, 200, 200), isGrayScale));
        addGenerator(std::make_shared<TimeGen>(4.0f, 15.0f));

        addGenerator(std::make_shared<VelocityGen>(ofVec3f(-10, -6, -10), ofVec3f(10, -20, 10)));
    }
};