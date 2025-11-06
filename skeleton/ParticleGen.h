#pragma once
#include "Particle.h"
class ParticleGen: public Particle
{
public:
	ParticleGen(MVector3 Pos, MVector3 vel, MVector3 accel, float dumping, double maxTimeLife,float size = 5, Vector4 sV = Vector4(1, 1, 1, 1));
	ParticleGen(MVector3 Pos, MVector3 vel, MVector3 accel, float dumping, double maxTimeLife, float size, physx::PxShape* s, Vector4 sV = Vector4(1, 1, 1, 1));
	~ParticleGen();

	bool updateTimeLife(double t);
protected:
	double timeLife;
	double maxTimeLife;
};

