#pragma once
#include <PxPhysicsAPI.h>
#include "core.hpp"
#include "RenderUtils.hpp"
#include <vector>
#include "Particle.h"
class MyScene
{
public:
	MyScene();
	~MyScene();

	void update(double t);
private:
	void createAxis();
	void chooseScene(int id);
	void scene0(); 
	void scene1();
	std::vector<RenderItem*> mItems;
	std::vector<Particle*> mParticles;
};

