#pragma once
#include "uniformGenerator.h"
#include "ForceGenerator.h"
class uniformGeneratorWithForces : public uniformGenerator
{
public:
	uniformGeneratorWithForces(int maxParticles, double emisionVel, mVector3D genPos, mVector3D genPosOffsetMin,
		mVector3D genPosOffsetMax, mVector3D genVel, mVector3D genVelOffsetMin, mVector3D genVelOffsetMax,
		mVector3D genAccel, mVector3D genAccelOffsetMin, mVector3D genAccelOffsetMax,
		double timeLifeMin, double timeLifeMax, double maxDistance, bool active,float mass, Vector4 sV);
	virtual void generate(double t) override;
	inline virtual void addForceGenerator(ForceGenerator* fg) { fG.push_back(fg); }
protected:
	float mass;
	std::list<ForceGenerator*> fG;
};

