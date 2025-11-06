#include "Ball.h"
#include "ParticleSystem.h"

Ball::Ball(MVector3 pos, MVector3 moveDir, double speed, float dumping, float mass, float timeLife, float size, Vector4 sV):
ParticleWithMass(pos, MVector3(0, 0, 0), MVector3(0, 0, 0), dumping, mass, timeLife, size, sv)
{
}

Ball::~Ball()
{
}
