#include "SolidGenerator.h"

SolidGenerator::SolidGenerator(PxScene* gScene, PxPhysics* gPhysics,int maxParticles, double emisionVel, Vector3 genPos, Vector3 genPosOffset,
	Vector3 genVel,Vector3 genVelOffset, Vector3 genAngVel, Vector3 genAngVelOffset, double staticFrictionMin, double dynamicFrictionMin,
	double restitutionMin, double staticFrictionMax, double dynamicFrictionMax,double restitutionMax,double timeLifeMin,
	double timeLifeMax, double maxDistance,bool active, float density,PxShape* shape, Vector4 sV):
	gScene(gScene), gPhysics(gPhysics),maxParticles(maxParticles), emisionVel(0), iniEmisionVel(emisionVel),genPos(genPos),
	genPosOffset(genPosOffset), genVel(genVel),genVelOffset(genVelOffset), genAngVel(genAngVel), genAngVelOffset(genAngVelOffset),
	timeLifeMin(timeLifeMin), timeLifeMax(timeLifeMax),maxDistance(maxDistance), active(active), nParticles(0), sV(sV),
	staticFrictionMax(staticFrictionMax), dynamicFrictionMax(dynamicFrictionMax),restitutionMax(restitutionMax), staticFrictionMin(staticFrictionMin),
	dynamicFrictionMin(dynamicFrictionMin), restitutionMin(restitutionMin), shape(shape), density(density)
{
	listS = std::list<SolidDynamic*>();
	listStoKill = std::list<SolidDynamic*>();
}

SolidGenerator::~SolidGenerator()
{
	for (SolidDynamic* s : listS) {
		delete s;
		s = nullptr;
	}
	listS.clear();
}

void SolidGenerator::update(double t) {
	if (active && (maxParticles <= 0 || nParticles < maxParticles))
		generate(t);

	for (SolidDynamic* s : listS) {
		if (s->updateTimeLife(t))
			s->integrate(t);
		else
			listStoKill.emplace_back(s);
	}

	killParts();
}

void SolidGenerator::killParts() {

	for (SolidDynamic* s : listStoKill) {
		listS.remove(s);
		if (s != nullptr) {
			delete s;
			s = nullptr;
		}
		nParticles--;
	}
	listStoKill.clear();
}

