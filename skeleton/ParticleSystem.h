#pragma once
#include <list>
#include "ParticleGenerator.h"
class ParticleSystem
{
public:
	ParticleSystem();
	virtual ~ParticleSystem();
	void addParticleGen(ParticleGenerator* pG);
	void removeParticleGen(ParticleGenerator* pG);
	void update(double t);
	void moveTo(Vector3 v);
	void setActive(bool a);
	bool getActive() { return active;}
private:
	std::list<ParticleGenerator*> mPGs;
	bool active = true;
};

