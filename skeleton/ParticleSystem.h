#pragma once
#include <list>
#include "ParticleGenerator.h"
class ParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem();
	void addParticleGen(ParticleGenerator* pG);
	void removeParticleGen(ParticleGenerator* pG);
	void update(double t);
	void moveTo(Vector3 v);
private:
	std::list<ParticleGenerator*> mPGs;
};

