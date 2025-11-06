#pragma once
#include "ParticleGenerator.h"
#include <random> 
class uniformGenerator: public ParticleGenerator
{
public:
	uniformGenerator(int maxParticles, double emisionVel, mVector3D genPos, mVector3D genPosOffsetMin,
		mVector3D genPosOffsetMax, mVector3D genVel, mVector3D genVelOffsetMin, mVector3D genVelOffsetMax,
		mVector3D genAccel, mVector3D genAccelOffsetMin, mVector3D genAccelOffsetMax,
		double timeLifeMin, double timeLifeMax, double maxDistance, bool active,Vector4 sV);
	virtual void generate(double t);
protected:
	std::mt19937 random;
	mVector3D genPosOffsetMin;
	mVector3D genVelOffsetMin;
	mVector3D genAccelOffsetMin;
};

