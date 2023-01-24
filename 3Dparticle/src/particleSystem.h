#pragma once

#include "ofMain.h"
#include "particle.h"
#include "particlesContainer.h"

class Generator
{
public:
	Generator() {}
	~Generator() {}

	virtual void generate(float dt, ParticlesContainer *p, size_t startId, size_t endId) = 0;
};

class Emitter
{
public:
	std::vector<std::shared_ptr<Generator>> generators;
	float emitRate{0.0};
	ofVec3f center;

	Emitter(float emitRate, ofVec3f center) : emitRate(emitRate), center(center) {}

	virtual void emit(float dt, ParticlesContainer *p)
	{
		size_t maxNumNParticles = dt * emitRate;
		size_t startId = p->alive;
		size_t endId = (startId + maxNumNParticles) > p->maxSize ? p->maxSize : (startId + maxNumNParticles);

		for (auto &generator : generators)
		{
			generator->generate(dt, p, startId, endId);
		}

		for (; startId < endId; ++startId)
		{
			p->wake(startId);
		}
	}

	void addGenerator(std::shared_ptr<Generator> gen) { generators.push_back(gen); }
};

class Updater
{
public:
	Updater() {}
	~Updater() {}

	virtual void update(float dt, ParticlesContainer *p);
};

class ParticleSystem
{

public:
	ParticlesContainer container;

	// size_t m_count;

	std::vector<std::shared_ptr<Emitter>> emitters;
	std::vector<std::shared_ptr<Updater>> updaters;

	ParticleSystem()
	{
		container.maxSize = 5000;
		container.particles.resize(5000);
	}
	explicit ParticleSystem(size_t maxCount)
	{
		container.maxSize = maxCount;
		container.particles.resize(maxCount);
		container.alive = maxCount - 1;
	}

	void update(float dt)
	{
		for (auto &emitter : emitters)
			emitter->emit(dt, &container);

		for (auto &updater : updaters)
			updater->update(dt, &container);
	}

	void draw()
	{
		for (size_t i = 0; i < container.alive; ++i)
		{
			container.particles[i].draw();
		}
	}

	size_t numAllParticles() const { return container.particles.size(); }
	size_t numAliveParticles() const { return container.alive; }

	void addEmitter(std::shared_ptr<Emitter> em) { emitters.push_back(em); }
	void addUpdater(std::shared_ptr<Updater> up) { updaters.push_back(up); }
};