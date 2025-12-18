#pragma once
#include "SolidGenerator.h"
#include "ForceGenerator.h"
#include <random> 
class UniformSolidGenerator : public SolidGenerator
{

public:
	UniformSolidGenerator(PxScene* gScene, PxPhysics* gPhysicsint,int maxParticles, double emisionVel, Vector3 genPos,
		Vector3 genPosOffsetMin,Vector3 genPosOffsetMax, Vector3 genVel, Vector3 genVelOffsetMin, Vector3 genVelOffsetMax,
		Vector3 genAccel, Vector3 AngVelOffsetMin, Vector3 AngVelOffsetMax, double staticFrictionMin, double dynamicFrictionMin,
		double restitutionMin, double staticFrictionMax, double dynamicFrictionMax, double restitutionMax,
		double timeLifeMin, double timeLifeMax, double maxDistance, bool active, float density,PxShape* shape, Vector4 sV);
	virtual ~UniformSolidGenerator();
	virtual void generate(double t) override;
	inline virtual void addForceGenerator(ForceGenerator* fg) { fG.push_back(fg); }
protected:
	std::list<ForceGenerator*> fG;


	std::mt19937 random;
	Vector3 genPosOffsetMin;
	Vector3 genVelOffsetMin;
	Vector3 genAngVelOffsetMin;
};

