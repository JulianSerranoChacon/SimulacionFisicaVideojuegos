#pragma once
#include "Particle.h"
class ParticleGen: public Particle
{
public:
	ParticleGen();
	~ParticleGen();

	bool updateTimeLife();
protected:
	double timeLife;
	double maxTimeLife;
};

