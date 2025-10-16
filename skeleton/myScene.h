#pragma once
#include <PxPhysicsAPI.h>
#include "core.hpp"
#include "RenderUtils.hpp"
#include <vector>

class Particle;

class myScene
{
public:
	myScene();
	~myScene();

	void update(float t);

	void Shoot();
private:
	void createAxis();
	void chooseScene(int id);
	void scene0();
	void scene1();
	void scene2();
	std::vector<RenderItem*> mItems;
	std::vector<Particle*> mParticles;
};