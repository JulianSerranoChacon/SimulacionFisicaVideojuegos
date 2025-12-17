#pragma once
#include "SolidDynamic.h"
#include <list>
#include <PxPhysicsAPI.h>


using namespace physx;
class SolidGenerator
{
public:
	SolidGenerator(PxScene* gScene, PxPhysics* gPhysics, int maxParticles, double emisionVel, Vector3 genPos, Vector3 genPosOffset, Vector3 genVel, Vector3 genVelOffset,
		Vector3 genAccel, Vector3 genAccelOffset,
		double timeLifeMin, double timeLifeMax, double maxDistance, bool active, Vector4 sV);
	virtual ~SolidGenerator();
	virtual void update(double t);
	virtual void generate(double t) = 0;
	inline virtual void setActive(bool Active) { active = Active; }
	//void moveTo(Vector3 point);
protected:
	virtual void killParts();
	int maxParticles;
	int nParticles;
	std::list<SolidDynamic*> listS;
	std::list<SolidDynamic*> listStoKill;
	double emisionVel;
	double iniEmisionVel;
	Vector3 genPos;
	Vector3 genPosOffset;
	Vector3 genVel;
	Vector3 genVelOffset;
	Vector3 genAccel;
	Vector3 genAccelOffset;
	double timeLifeMin;
	double timeLifeMax;
	double maxDistance;
	bool active;
	Vector4 sV;
	PxScene* gScene;
	PxPhysics* gPhysics;
};

