#pragma once
#include <PxPhysicsAPI.h>
#include "core.hpp"
#include "RenderUtils.hpp"
#include <vector>

class myScene
{
public:
	myScene();
	~myScene();
private:
	void createAxis();
	std::vector<RenderItem*> mItems;
};