#include "ParticleGenerator.h"
#include "ParticleGen.h"


ParticleGenerator::ParticleGenerator(int maxParticles, double emisionVel, mVector3D genPos, mVector3D genPosOffset,mVector3D genVel, mVector3D genVelOffset, mVector3D genAccel,
	mVector3D genAccelOffset,double timeLifeMin, double timeLifeMax, double maxDistance, bool active): maxParticles(maxParticles), emisionVel(0), iniEmisionVel(emisionVel),
	genPos(genPos), genPosOffset(genPosOffset),genVel(genVel),genVelOffset(genVelOffset),genAccel(genAccel), genAccelOffset(genAccelOffset),
	timeLifeMin(timeLifeMin), timeLifeMax(timeLifeMax), maxDistance(maxDistance), active(active), nParticles(0)
{
	listP = std::list<ParticleGen*>();
	listPtoKill = std::list<ParticleGen*>();
}

ParticleGenerator::~ParticleGenerator()
{
	for (ParticleGen* p : listP) {
		delete p;
		p = nullptr;
	}
	listP.clear();
}

void ParticleGenerator::update(double t)
{
	if (active && (maxParticles <= 0 || nParticles < maxParticles))
		generate(t);

	for (ParticleGen* p : listP) {
		if (p->updateTimeLife(t))
			p->integrate(t);
		else
			listPtoKill.emplace_back(p);
	}

	killParts();
}

void ParticleGenerator::killParts()
{
	for (ParticleGen* p : listPtoKill) {
		listP.remove(p);
		if (p != nullptr) {
			delete p;
			p = nullptr;
		}
		nParticles--;
	}
	listPtoKill.clear();
}
