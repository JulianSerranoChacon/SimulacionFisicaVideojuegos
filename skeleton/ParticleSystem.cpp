#include "ParticleSystem.h"
#include "ParticleGenerator.h"
ParticleSystem::ParticleSystem()
{
	mPGs = std::list<ParticleGenerator*>();
}

ParticleSystem::~ParticleSystem()
{
	for(ParticleGenerator* pG : mPGs) {
		delete pG;
	}
	mPGs.clear();
}

void ParticleSystem::addParticleGen(ParticleGenerator* pG)
{
	mPGs.push_back(pG);
}

void ParticleSystem::removeParticleGen(ParticleGenerator* pG)
{
	mPGs.remove(pG);
	delete pG;
	pG = nullptr;
}

void ParticleSystem::update(double t)
{
	for (ParticleGenerator* pG : mPGs) {
		pG->update(t);
	}
}
