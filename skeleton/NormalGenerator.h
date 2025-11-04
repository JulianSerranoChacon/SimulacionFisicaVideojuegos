#pragma once
#include <random>
#include "ParticleGenerator.h"
class NormalGenerator: public ParticleGenerator
{
public:
	NormalGenerator(int maxParticles, double emisionVel, mVector3D genPos, mVector3D genPosOffset, mVector3D genVel, mVector3D genVelOffset,
		mVector3D genAccel, mVector3D genAccelOffset,
		double timeLifeMin, double timeLifeMax, double maxDistance, bool active, double media, double desviacion);
	virtual void generate(double t);

private:
	std::mt19937 random;
	double media;
	double desviacion;
};

