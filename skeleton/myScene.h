#pragma once
#include <PxPhysicsAPI.h>
#include "core.hpp"
#include "RenderUtils.hpp"
#include <vector>

class Particle;
class ParticleSystem;

class myScene
{
public:
	myScene();
	~myScene();

	void update(float t);

	void Shoot(physx::PxVec3 camPos, physx::PxVec3 camDir);
private:
	void createAxis();
	void chooseScene(int id);
	void scene0();
	void scene1();
	void scene2();
	void scene3();
	void scene4();
	std::vector<RenderItem*> mItems;
	std::vector<Particle*> mParticles;
	std::vector< ParticleSystem*> mPSystems;
};