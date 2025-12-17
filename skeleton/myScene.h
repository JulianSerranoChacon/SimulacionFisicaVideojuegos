#pragma once
#include <PxPhysicsAPI.h>
#include "core.hpp"
#include "RenderUtils.hpp"
#include <vector>
#include <map>

class Particle;
class ParticleSystem;
class Car;
class ForceGenerator;
class myScene
{
public:
	myScene();
	~myScene();

	void update(float t);

	void Shoot(physx::PxVec3 camPos, physx::PxVec3 camDir);
	void moveCar(Vector3 moveDir);
	void toggleTurbo();
	void iniLLuvia();
	void stopMPSystems(std::string s);
	void toggleMFG(std::string s);
private:
	void createAxis();
	void chooseScene(int id);
	void scene0();
	void scene1();
	void scene2();
	void scene3();
	void scene4();
	void scene5();
	void scene6();
	void gameScene();
	std::vector<RenderItem*> mItems;
	std::vector<Particle*> mParticles;
	std::map<std::string, ParticleSystem*> mPSystems;
	std::map<std::string, ForceGenerator*> mFG;
	Car* mCar;
};