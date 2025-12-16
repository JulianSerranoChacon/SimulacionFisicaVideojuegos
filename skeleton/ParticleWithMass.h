#pragma once
#include "ParticleGen.h"
#include "ForceGenerator.h"
#include <list>
class ParticleWithMass : public ParticleGen
{
public:
	ParticleWithMass(MVector3 pos, MVector3 velReal, MVector3 accel, float dumping, float mass,float timeLife,float size, Vector4 sV = Vector4(1, 1, 1, 1));
	ParticleWithMass(MVector3 pos, MVector3 velReal, MVector3 accel, float dumping, float mass, float timeLife, float size, physx::PxShape* s, Vector4 sV = Vector4(1, 1, 1, 1));
	virtual ~ParticleWithMass();
	inline virtual float getMass() { return mass; }
	inline virtual MVector3 getVel() { return vel_; }
	inline virtual MVector3 getAccel() { return accel_; }
	inline virtual Vector3 getPos() { return pose_.p; }
	virtual void integrate(double t);
	inline virtual void addForceGenerator(ForceGenerator* fg) { fG.push_back(fg); }
	inline virtual void addAcceleration(mVector3D vecToAdd) { accel_ += vecToAdd; }
protected:
	std::list<ForceGenerator*> fG;
	float mass;
	MVector3 force;
};