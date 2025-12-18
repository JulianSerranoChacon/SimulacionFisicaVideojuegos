#pragma once
#include "ParticleSystem.h"
#include "SolidDynamic.h"
class Proyectil;
class Car : public SolidDynamic
{
public:
	Car(PxScene* gScene, PxPhysics* gPhysics, PxShape* shape, PxTransform& transform, double density,
		double staticFriction, double dynamicFriction, double restitution, double speed,double maxSpeed, double damping,
		Vector4& color = Vector4(1));
	~Car();
	virtual Proyectil* shoot();
	virtual void integrate(double t) override;
	virtual void applyMove(Vector3& dir, double t);
	virtual void move(const Vector3& dir);
	inline void setPS(ParticleSystem* p) { pS = p; }
	inline void setPSActive(bool active) { pS->setActive(active); }
	inline bool isPSActive() { return pS->getActive(); }
protected:
	Vector3 moveDir;
	ParticleSystem* pS = nullptr;
	double speed;
	double damping;
	double maxSpeed;
};

