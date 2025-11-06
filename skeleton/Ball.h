#pragma once
#include "ParticleWithMass.h"
class ParticleSystem;
class Ball :public ParticleWithMass
{
public:
	Ball(MVector3 pos, MVector3 moveDir, double speed, float dumping, float mass, float timeLife, float size, Vector4 sV);
	~Ball();

	inline void setPS(ParticleSystem* p) { pS = p; }
protected:
	ParticleSystem* pS = nullptr;
};

