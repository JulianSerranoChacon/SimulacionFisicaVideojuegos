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
class SolidStatic;
class SolidDynamic;
class SolidSystem;
class SolidGenerator;
using namespace physx;
class myScene
{
public:
	myScene(PxScene* gScene, PxPhysics* gPhysics);
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
	void scene7();
	void scene8();
	void scene9();
	void GameScene();
	void PoyectoIntermedioScene();
	void configureCar();
	std::vector<RenderItem*> mItems;
	std::vector<Particle*> mParticles;
	std::vector<SolidStatic*> mSolidsStatics;
	std::vector<SolidDynamic*> mSolidDynamics;
	std::map<std::string, ParticleSystem*> mPSystems;
	std::map<std::string, ForceGenerator*> mFG;
	std::map<std::string, SolidSystem*> mSSystems;
	Car* mCar = nullptr;
	PxScene* gScene = nullptr;
	PxPhysics* gPhysics = nullptr;
};