#pragma once
#include "ParticleWithMass.h"
#include "ParticleSystem.h"
#include "gravityForceGenerator.h"
class Proyectil;
class Car : public ParticleWithMass
{
public:
	Car(MVector3 pos, MVector3 moveDir, double speed, float dumping, float mass, float timeLife, float sizeX, float sizeY, float sizeZ, Vector4 sV);
	~Car();
	inline virtual void setForceToAply(mVector3D f) {for (ForceGenerator* fg : fG) if (fg != nullptr)fg->setForceToAply(f);}
	virtual Proyectil* shoot();
	virtual void integrate(double t) override;
	virtual void move(Vector3);
	inline void setPS(ParticleSystem* p) { pS = p; }
	inline void setPSActive(bool active) { pS->setActive(active); }
	inline bool isPSActive() { return pS->getActive(); }
protected:
	MVector3 moveDir;
	ParticleSystem* pS = nullptr;
	double speed;
	float size;
};

