#pragma once
#include <list>
class ParticleGenerator;
class ParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem();
	void addParticleGen(ParticleGenerator* pG);
	void removeParticleGen(ParticleGenerator* pG);
	void update(double t);
private:
	std::list<ParticleGenerator*> mPGs;
};

