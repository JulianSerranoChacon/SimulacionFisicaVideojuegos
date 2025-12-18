#pragma once
#include "SolidGenerator.h"
#include <random>
class NormalSolidGenerator : public SolidGenerator
{
public:
	NormalSolidGenerator(double media, double desviacion, PxScene* gScene, PxPhysics* gPhysics, int maxParticles, double emisionVel, Vector3 genPos, Vector3 genPosOffset,
		Vector3 genVel, Vector3 genVelOffset, Vector3 genAngVel, Vector3 genAccelOffset, double staticFrictionMin, double dynamicFrictionMin,
		double restitutionMin, double staticFrictionMax, double dynamicFrictionMax, double restitutionMax, double timeLifeMin,
		double timeLifeMax, double maxDistance, bool active, float density, PxShape* shape, Vector4 sV);
	~NormalSolidGenerator();

	virtual void generate(double t);
	inline virtual void addForceGenerator(ForceGenerator* fg) { fG.push_back(fg); }
private:
	std::list<ForceGenerator*> fG;
	std::mt19937 random;
	double media;
	double desviacion;
};

