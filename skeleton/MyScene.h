#pragma once
#include <PxPhysicsAPI.h>
#include "core.hpp"
#include "RenderUtils.hpp"
#include <vector>
class MyScene
{
public:
	MyScene();
	~MyScene();
private:
	void createAxis();
	std::vector<RenderItem*> mItems;
};

