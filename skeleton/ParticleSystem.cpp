#include "ParticleSystem.h"
ParticleSystem::ParticleSystem()
{
	mPGs = std::list<ParticleGenerator*>();
}

ParticleSystem::~ParticleSystem()
{
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

void ParticleSystem::moveTo(Vector3 v)
{
	for (ParticleGenerator* pG : mPGs) {
		if(pG != nullptr)
			pG->moveTo(v);
	}
}

void ParticleSystem::setActive(bool a)
{
	active = a;
	for (ParticleGenerator* pG : mPGs) {
		if (pG != nullptr)
			pG->setActive(active);
	}
}
