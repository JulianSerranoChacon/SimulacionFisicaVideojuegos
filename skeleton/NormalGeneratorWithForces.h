#pragma once
#include "NormalGenerator.h"
#include "ForceGenerator.h"
class NormalGeneratorWithForces: public NormalGenerator
{
public:
	NormalGeneratorWithForces(int maxParticles, double emisionVel, mVector3D genPos, mVector3D genPosOffset, mVector3D genVel, mVector3D genVelOffset,
		mVector3D genAccel, mVector3D genAccelOffset,
		double timeLifeMin, double timeLifeMax, double maxDistance, bool active, double media, double desviacion,float mass, Vector4 sV);
	virtual void generate(double t);
	inline virtual void addForceGenerator(ForceGenerator* fg) { fG.push_back(fg); }
protected:
	float mass;
	std::list<ForceGenerator*> fG;
};

