#pragma once
#include <list>
#include "Vector3D.h"
#include "Particle.h"
class ParticleGen;
using mVector3D = Vector3D<float>;
class ParticleGenerator
{
public:
	ParticleGenerator(int maxParticles, double emisionVel, mVector3D genPos, mVector3D genPosOffset, mVector3D genVel, mVector3D genVelOffset,
		mVector3D genAccel, mVector3D genAccelOffset,
		double timeLifeMin, double timeLifeMax, double maxDistance, bool active, Vector4 sV);
	virtual ~ParticleGenerator();
	virtual void update(double t);
	virtual void generate(double t) = 0;
	inline virtual void setActive(bool Active) { active = Active; }
	void moveTo(Vector3 point);
protected:
	virtual void killParts();
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
	Vector4 sV;
};

