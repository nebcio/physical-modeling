#pragma once

#include "ofMain.h"
#include "particle.h"

class ParticlesContainer
{
public:
    int maxSize = 5000;
    int alive = 0;

    std::vector<Particle> particles;

    ParticlesContainer() {}
    ParticlesContainer(int maxSize) : maxSize(maxSize) {}
    ~ParticlesContainer() {}

    void generate(size_t maxSize)
    {
        alive = 0;
    }

    void kill(size_t id)
    {
        std::swap(particles[id], particles[alive - 1]); // ?
    }

    void wake(size_t id)
    {
        ++alive;
    }

    void swapData(size_t a, size_t b)
    {
    }
};
