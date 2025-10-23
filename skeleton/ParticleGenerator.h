#pragma once
#include <list>
#include "Vector3D.h"
class ParticleGen;
using mVector3D = Vector3D<float>;
class Generator
{
public:
	Generator(int maxParticles, double emisionVel, mVector3D genPos, mVector3D genPosOffset, mVector3D genVel, mVector3D genVelOffset,
		mVector3D genAccel, mVector3D genAccelOffset,
		double timeLifeMin, double timeLifeMax, double maxDistance, bool active);
	virtual ~Generator();
	virtual void update(double t);
	virtual void generate() = 0;
protected:
	virtual void killParts(ParticleGen* particula);
	int maxParticles;
	int nParticles;
	std::list<ParticleGen*> listP;
	std::list<ParticleGen*> listPtoKill;
	double emisionVel;
	double iniEmisionVel;
	mVector3D genPos;
	mVector3D genPosOffset;
	mVector3D genVel;
	mVector3D genVelOffset;
	mVector3D genAccel;
	mVector3D genAccelOffset;
	double timeLifeMin;
	double timeLifeMax;
	double maxDistance;
	bool active;
};

