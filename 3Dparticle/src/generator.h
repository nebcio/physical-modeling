#pragma once

#include "ofMain.h"
#include "particleSystem.h"

class SpherePositionGen : public Generator
{
public:
    ofVec3f center;
    float radHor;

    SpherePositionGen() : center(0.0), radHor(0.0) {}

    SpherePositionGen(const ofVec3f &center, float radHor)
        : center(center), radHor(radHor)
    {
    }

    void generate(float dt, ParticlesContainer *p, size_t startId, size_t endId)
    {

        for (size_t i = startId; i < endId; ++i)
        {
            float theta = ofRandom(2 * PI);
            float phi = ofRandom(2 * PI);

            float x = center.x + radHor * sin(theta) * cos(phi);
            float y = center.y + radHor * sin(theta) * sin(phi);
            float z = center.z + radHor * cos(theta);

            p->particles[i].pos = ofVec3f(x, y, z);
        }
    }
};

class BoxPositionGen : public Generator
{
public:
    ofVec3f minPosition;
    ofVec3f maxPosition;

    BoxPositionGen(ofVec3f minPosition, ofVec3f maxPosition)
        : minPosition(minPosition), maxPosition(maxPosition)
    {
    }

    void generate(float dt, ParticlesContainer *p, size_t startId, size_t endId)
    {

        for (size_t i = startId; i < endId; ++i)
        {
            p->particles[i].pos = ofVec3f(ofRandom(minPosition.x, maxPosition.x), 
                                          ofRandom(minPosition.y, maxPosition.y), 
                                          ofRandom(minPosition.z, maxPosition.z));
        }
    }
};

class ColorGen : public Generator
{
public:
    ofColor startColor;
    ofColor endColor;
    bool isGrayScale;

    ColorGen() : startColor(0, 0, 0), endColor(255, 255, 255) {}

    ColorGen(ofColor startColor, ofColor endColor, bool isGrayScale = false)
        : startColor(startColor), endColor(endColor), isGrayScale(isGrayScale)
    {
    }

    void generate(float dt, ParticlesContainer *p, size_t startId, size_t endId)
    {
        for (size_t i = startId; i < endId; ++i)
        {
            if (isGrayScale)
                p->particles[i].color = ofColor(ofRandom(startColor.r, endColor.r));
            else
                p->particles[i].color = ofColor(ofRandom(startColor.r, endColor.r), ofRandom(startColor.g, endColor.g), ofRandom(startColor.b, endColor.b), 200);
        }
    }
};

class TimeGen : public Generator
{
public:
    float minTimeLife;
    float maxTimeLife;

    TimeGen(float minTimeLife, float maxTimeLife)
        : minTimeLife(minTimeLife), maxTimeLife(maxTimeLife)
    {
    }

    void generate(float dt, ParticlesContainer *p, size_t startId, size_t endId)
    {
        for (size_t i = startId; i < endId; ++i)
        {
            float timeLife = ofRandom(minTimeLife, maxTimeLife);
            p->particles[i].timeLife = { timeLife, timeLife };
        }
    }
};

class VelocityGen : public Generator
{
public:
    ofVec3f minVelocity;
    ofVec3f maxVelocity;

    VelocityGen() : minVelocity(0.0), maxVelocity(10.0) {}

    VelocityGen(ofVec3f minVelocity, ofVec3f maxVelocity)
        : minVelocity(minVelocity), maxVelocity(maxVelocity)
    {
    }

    void generate(float dt, ParticlesContainer *p, size_t startId, size_t endId)
    {
        for (size_t i = startId; i < endId; ++i)
        {
            p->particles[i].vel = ofVec3f(ofRandom(minVelocity.x, maxVelocity.x),
                                          ofRandom(minVelocity.y, maxVelocity.y),
                                          ofRandom(minVelocity.z, maxVelocity.z));
        }
    }
};