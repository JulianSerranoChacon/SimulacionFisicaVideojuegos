#pragma once
#include "Particle.h"

using MVector3 = Vector3D<float>;

class Proyectil: public Particle
{
public:
	Proyectil(MVector3 pos, MVector3 velReal, MVector3 accel, float dumping, float mass, float gravity, MVector3 vSim);
	virtual ~Proyectil();

	virtual void integrate(double t);
protected:
	virtual void appGravity(double t);

	//masas
	float mReal;
	float mSim;
	//gravedades
	float gReal;
	float gSim;
	//velocidad simulada
	MVector3 vSim;
};

