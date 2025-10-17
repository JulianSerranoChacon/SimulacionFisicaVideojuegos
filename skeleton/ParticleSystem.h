#pragma once
#include <list>
class Particle;
class ParticleSystem
{
public:
	ParticleSystem();
	virtual ~ParticleSystem();
	virtual void update();
protected:
	virtual void killParts();
	unsigned int maxParticles;
	std::list<Particle*> listP;
	std::list<Particle*> listKilled;
	float angle;
	double timeLifeMin;
	double timeLifeMax;
	double maxDistance;
};

