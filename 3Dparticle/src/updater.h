#pragma once

#include "ofMain.h"
#include "particleSystem.h"

class EulerUpdater : public Updater
{
public:
    ofVec3f globalAcceleration;

    EulerUpdater() : globalAcceleration(0.0) {}

    void update(float dt, ParticlesContainer *p)
    {
        const ofVec3f globalA{dt * globalAcceleration.x, dt * globalAcceleration.y, dt * globalAcceleration.z};
        const float localDT = (float)dt;

        const unsigned int endId = p->alive;
        for (size_t i = 0; i < endId; ++i)
            p->particles[i].acc += globalA;

        for (size_t i = 0; i < endId; ++i)
            p->particles[i].vel += localDT * p->particles[i].acc;

        for (size_t i = 0; i < endId; ++i)
            p->particles[i].pos += localDT * p->particles[i].vel;
    }
};

class ColorUpdater : public Updater
{
public:
    ofVec3f center;

    ColorUpdater(ofVec3f center) : center(center) {}

    void update(float dt, ParticlesContainer *p)
    {
        const unsigned int endId = p->alive;
        for (size_t i = 0; i < endId; ++i)
        {
            ofVec3f diff = p->particles[i].pos - center;
            float dist = diff.length();
            float green = ofMap(dist, 0.0f, 25.0f, 255.0f, 0.0f, true);

            p->particles[i].color.g = green;
            p->particles[i].color.a = p->particles[i].timeLife.x / p->particles[i].timeLife.y * 200.0f;
        }
    }
};

class TimeUpdater : public Updater
{
public:

    TimeUpdater() {}

    void update(float dt, ParticlesContainer *p)
    {
        unsigned int endId = p->alive;

        for (size_t i = 0; i < endId; ++i)
        {
            p->particles[i].timeLife.x -= dt;
            if (p->particles[i].timeLife.x < 0.0f)
            {
                p->particles[i] = p->particles[p->alive - 1];
                --p->alive;
                --endId;
            }
        }
    }
};

class GravityUpdater : public Updater
{
public:
    float ground;

    GravityUpdater(float ground) : ground(ground) {}

    void update(float dt, ParticlesContainer *p)
    {
        for (size_t i = 0; i < p->alive; ++i) {
            if (p->particles[i].pos.y < ground) {
                p->particles[i].vel = ofVec3f(0.0f);    // sparks and snow stick to the ground
                p->particles[i].pos.y = ground;
            }
            else
                p->particles[i].vel.y -= 9.8f * dt;

        }
    }
};

// class AttractorUpdater : public Updater
// {
// protected:
//     std::vector<ofVec3f> attractors; // .w is force
// public:
//     virtual void update(double dt, ParticlesContainer *p)
//     {
//         const float localDT = (float)dt;

//         const size_t endId = p->alive;
//         const size_t countAttractors = attractors.size();
//         glm::vec4 off;
//         float dist;
//         size_t a;
//         for (size_t i = 0; i < endId; ++i)
//         {
//             for (a = 0; a < countAttractors; ++a)
//             {
//                 off.x = attractors[a].x - p->particles[i].pos.x;
//                 off.y = attractors[a].y - p->particles[i].pos.y;
//                 off.z = attractors[a].z - p->particles[i].pos.z;
//                 dist = glm::dot(off, off);

//                 // if (fabs(dist) > 0.00001)
//                 //dist = attractors[a].w / dist; !!!!!!

//                 p->particles[i].acc += off * dist;
//             }
//         }
//     }

//     size_t collectionSize() const { return attractors.size(); }
//     void add(const ofVec3f &attr) { attractors.push_back(attr); }
//     ofVec3f &get(size_t id) { return attractors[id]; }
// };
 
//         {
//             scaler = (p->particles[i].pos.x - minPos.x) / diffr;
//             scaleg = (p->particles[i].pos.y - minPos.y) / diffg;
//             scaleb = (p->particles[i].pos.z - minPos.z) / diffb;
//             p->particles[i].color.r = scaler; // glm::mix(p->startp->particles[i].color.r, p->endp->particles[i].color.r, scaler);
//             p->particles[i].color.g = scaleg; // glm::mix(p->startp->particles[i].color.g, p->endp->particles[i].color.g, scaleg);
//             p->particles[i].color.b = scaleb; // glm::mix(p->startp->particles[i].color.b, p->endp->particles[i].color.b, scaleb);
//             p->particles[i].color.a = glm::mix(p->particles[i].startCol.a, p->particles[i].endCol.a, p->particles[i].timeLife.z);
//         }
//     }
// };