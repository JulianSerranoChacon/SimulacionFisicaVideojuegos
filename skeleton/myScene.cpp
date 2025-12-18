#include "MyScene.h"
#include "Vector3D.h"
#include "Particle.h"
#include "Proyectil.h"
#include "ParticleSystem.h"
#include "NormalGenerator.h"
#include "uniformGenerator.h"
#include "NormalGeneratorWithForces.h"
#include "uniformGeneratorWithForces.h"
#include "gravityForceGenerator.h"
#include "WindForceGenerator.h"
#include "VortexForceGenerator.h"
#include "SpringForceGenerator.h"
#include "Car.h"
#include "BouyancyForceGenerator.h"
#include "SolidStatic.h"
#include "SolidDynamic.h"
#include "SolidSystem.h"
#include "SolidGenerator.h"
#include "uniformSolidGenerator.h"
#include "NormalSolidGenerator.h"
#include "ParticleWithMass.h"
#include "Ball.h"
#include "Filters.h"
#include "Goal.h"
#include "CollisionManager.h"

using namespace physx;

myScene::myScene(PxScene* gScene, PxPhysics* gPhysics): gScene(gScene), gPhysics(gPhysics)
{
	//chooseScene(9);
	//PoyectoIntermedioScene();
	cM = new CollisionManager(this); //para la escena de juego
	gScene->setSimulationEventCallback(cM);
	GameScene();
}

myScene::~myScene()
{
	for (int i = 0; i < mParticles.size(); i++)
	{
		if (mParticles[i] != nullptr) {
			delete mParticles[i];
			mParticles[i] = nullptr;
		}
	}
	for (int i = 0; i < mItems.size(); i++) {
		if (mItems[i] != nullptr) {
			DeregisterRenderItem(mItems[i]);
			mItems[i] = nullptr;
		}
	}
	for (int i = 0; i < mSolidsStatics.size(); i++) {
		if (mSolidsStatics[i] != nullptr) {
			delete mSolidsStatics[i];
			mSolidsStatics[i] = nullptr;
		}
	}
	for (int i = 0; i < mSolidDynamics.size(); i++) {
		if (mSolidDynamics[i] != nullptr) {
			delete mSolidDynamics[i];
			mSolidDynamics[i] = nullptr;
		}
	}
	for (auto e : mPSystems) 
	{
		if (e.second != nullptr)
			delete e.second;
		e.second = nullptr;
	}
	for (auto s : mSSystems)
	{
		if (s.second != nullptr)
			delete s.second;
		s.second = nullptr;
	}
	for (auto e : mFG)
	{
		if (e.second != nullptr)
			delete e.second;
		e.second = nullptr;
	}
	if (mCar != nullptr) {
		delete mCar;
		mCar = nullptr;
	}

	if (mBall != nullptr) {
		delete mBall;
		mBall = nullptr;
	}

	if (g1 != nullptr) {
		delete g1;
		g1 = nullptr;
	}
}

void myScene::update(float t)
{
	for (int i = 0; i < mParticles.size(); i++)
		if (mParticles[i] != nullptr)
			mParticles[i]->integrate(t);

	for (auto pS : mPSystems)
		if(pS.second != nullptr)
			pS.second->update(t);

	for (auto SS : mSSystems)
		if(SS.second != nullptr)
			SS.second->update(t);

	for (int i = 0; i < mSolidDynamics.size(); i++) {
		if (mSolidDynamics[i] != nullptr) {
			mSolidDynamics[i]->integrate(t);
		}
	}

	if (mCar != nullptr);
		mCar->integrate(t);

		if (destroyBall) {
		resetBall();
		}

		if (isGoal && timeParts < maxTimeParts) {
			timeParts += t;
		}
		if (isGoal && timeParts >= maxTimeParts) {
			isGoal = false;
			fuegoG1->setActive(false);
			hoseG1->setActive(false);
		}
}

void myScene::Shoot(physx::PxVec3 camPos, physx::PxVec3 camDir)
{
	// Normalizamos la dirección de la cámara
	camDir.normalize();

	// Velocidad del proyectil
	float projectileSpeed = 250.0f;

	// Calculamos la velocidad inicial en dirección de la cámara
	Vector3D<float> initialVelocity(camDir.x * projectileSpeed,
		camDir.y * projectileSpeed,
		camDir.z * projectileSpeed);

	// Creamos el proyectil
	mParticles.push_back(new Proyectil(
		Vector3D<float>(camPos.x, camPos.y, camPos.z),  // posicion inicial
		initialVelocity,                                // velocidad inicial (hacia donde mira la camara)
		Vector3D<float>(0, 0, 0),                       // aceleracion inicial
		0.2f,                                           // damping
		20.0f,                                          // masa
		9.8f,                                           // gravedad
		Vector3D<float>(0, 0, 100)                      // tamano u otro parametro tuyo
	));

	if(mCar != nullptr)
		mParticles.push_back(mCar->shoot());
}

void myScene::moveCar(Vector3 moveDir)
{
	if(mCar != nullptr)
		mCar->move(moveDir);
}

void myScene::jumpCar()
{
	if (mCar != nullptr)
		mCar->jump();
}

void myScene::createAxis()
{
	Vector3D<float> vR(20, 0, 0);
	PxTransform* strR = new PxTransform(vR.toVector3());
	Vector4 svR = Vector4(1, 0, 0, 1);
	RenderItem* sphereR = new RenderItem(CreateShape(PxSphereGeometry(5)), strR, svR);
	mItems.push_back(sphereR);

	Vector3D<float> vG(0, 20, 0);
	PxTransform* strG = new PxTransform(vG.toVector3());
	Vector4 svG = Vector4(0, 1, 0, 1);
	RenderItem* sphereG = new RenderItem(CreateShape(PxSphereGeometry(5)), strG, svG);
	mItems.push_back(sphereG);

	Vector3D<float> vB(0, 0, 20);
	PxTransform* strB = new PxTransform(vB.toVector3());
	Vector4 svB = Vector4(0, 0, 1, 1);
	RenderItem* sphereB = new RenderItem(CreateShape(PxSphereGeometry(5)), strB, svB);
	mItems.push_back(sphereB);
}

void myScene::chooseScene(int id)
{

	//createAxis();
	switch (id)
	{
	case 0:
		scene0();
		break;
	case 1:
		scene1();
		break;
	case 2:
		scene2();
		break;
	case 3:
		scene3();
		break;
	case 4:
		scene4();
		break;
	case 5:
		scene5();
		break;
	case 6:
		scene6();
		break;
	case 7:
		scene7();
		break;
	case 8:
		scene8();
		break;
	case 9:
		scene9();
		break;
	default:
		break;
	}
}

void myScene::scene0()
{
	PxShape* s = CreateShape(PxSphereGeometry(5));
	PxTransform* str = new PxTransform(Vector3(0, 0, 0));
	Vector4 sv = Vector4(1, 1, 1, 1);
	RenderItem* sphere = new RenderItem(s, str, sv);
	mItems.push_back(sphere);
}

void myScene::scene1()
{
	//mParticles.push_back(new Particle(mVector3D(0, 0, 0), mVector3D(2, 0, 0), mVector3D(0, 5, 5), 0.2));
}

void myScene::scene2()
{
	mParticles.push_back(new Proyectil(Vector3D<float>(-30, -30, 0), Vector3D<float>(250, 250, 0), Vector3D<float>(0, 0, 0), 0.2, 2, 9.8, Vector3D<float>(100,100, 0)));
}

void myScene::scene3()
{
	ParticleSystem* myPS = new ParticleSystem();
	mPSystems.emplace("scene3Sys",myPS);

	//fuego
	ParticleGenerator* pG = new NormalGenerator(
		100, 0.03,                      // numero particulas, velocidad de emision
		mVector3D(0, 0, 0),             // Posicion
		mVector3D(1, 0.5, 1),           // Offset de la posicion
		mVector3D(0, 8, 0),             // velocidad
		mVector3D(2, 3, 2),             // Offset de la velocidad
		MVector3(0, 2, 0),              // aceleracion
		MVector3(0, 1, 0),              // Offset de la aceleracion
		1, 3, 60,                       // vida minia, maxima y distancia
		true,							// Active
		0.0, 0.4,                       // media y desviacion
		Vector4(1, 0.5, 0, 1)           // color
	);
	myPS->addParticleGen(pG);

	// Generador de lluvia
	pG = new uniformGenerator(
		100,                  // Ma ximo de particulas
		0.07,                 // Tiempo entre emisiones
		mVector3D(0, 30, 0),    // Posicion del generador (altura)
		MVector3(0, 0, 0),      // Offset minimo de posicion
		mVector3D(60, 0, 60),   // Offset maximo de posicion (ancho y profundidad del cuadrado)
		MVector3(0, -25, 0),    // Velocidad
		MVector3(0, -2, 0),     // Offset minimo de la velocidad 
		MVector3(0, 0, 0),      // Offset maximo de la velocidad a
		MVector3(0, 0, 0),      // Aceleracion
		MVector3(0, 0, 0),      // Offset minimo de la aceleracion
		MVector3(0, 0, 0),      // Offset maximo de la maxima
		1,                  // Tiempo de vida minimo
		2,                  // Tiempo de vida maximo
		50.0,                 // Distancia maxima
		true,                 // Activo
		Vector4(0.6, 0.7, 1.0, 1) // Color azul
	);
	myPS->addParticleGen(pG);



	//humo
	// Generador de humo
	pG = new uniformGenerator(
		200,                     // Maximo de particulas
		0.05,                    // Tiempo entre emisiones
		mVector3D(30, 30, 30),   // Posicion
		mVector3D(-5, -5, -5),   // Offset minimo de posicion (cubo alrededor del centro)
		mVector3D(5, 5, 5),      // Offset maximo de posicion
		mVector3D(0, 0, 0),      // Velocidad 
		mVector3D(-1, -1, -1),   // Offset minimo de velocidad (hacia todas direcciones)
		mVector3D(1, 1, 1),      // Offset maximo de velocidad
		mVector3D(0, -10, 0),      // Aceleracion
		mVector3D(0, 0, 0),      // Offset minimo de aceleracion
		mVector3D(0, 0, 0),      // Offset maximo de aceleracion
		2,                        // Tiempo de vida minimo
		4,                        // Tiempo de vida maximo
		10,                       // Distancia maxima
		true,                     // Activo
		Vector4(0.5, 0.5, 0.5, 1) // Color gris
	);
	myPS->addParticleGen(pG);
}

void myScene::scene4()
{
	ParticleSystem* myPS = new ParticleSystem();
	mPSystems.emplace("scene4Sys",myPS);

	gravityForceGenerator* gG = new gravityForceGenerator(mVector3D(0, -1000, 0));
	WindForceGenerator* wG = new WindForceGenerator(mVector3D(500,500,0 ), 0.8f);
	VortexForceGenerator* vG = new VortexForceGenerator(mVector3D(30, 30, 30),30,10,30);

	//fuego
	NormalGeneratorWithForces* pG = new NormalGeneratorWithForces(
		300, 0.003,                      // numero particulas, velocidad de emision
		mVector3D(0, 0, 0),             // Posicion
		mVector3D(1, 0.5, 1),           // Offset de la posicion
		mVector3D(0, 8, 0),             // velocidad
		mVector3D(2, 3, 2),             // Offset de la velocidad
		MVector3(0, 2, 0),              // aceleracion
		MVector3(0, 1, 0),              // Offset de la aceleracion
		1, 3, 60,                       // vida minia, maxima y distancia
		true,							// Active
		0.0, 0.4,                       // media y desviacion
		50,								//masa
		Vector4(1, 0.5, 0, 1)           // color
	);
	//pG->addForceGenerator(gG);
	pG->addForceGenerator(wG);
	pG->addForceGenerator(vG);
	myPS->addParticleGen(pG);

	// Generador de lluvia
	uniformGeneratorWithForces* pG2 = new uniformGeneratorWithForces(
		100,                  // Ma ximo de particulas
		0.07,                 // Tiempo entre emisiones
		mVector3D(0, 30, 0),    // Posicion del generador (altura)
		MVector3(0, 0, 0),      // Offset minimo de posicion
		mVector3D(60, 0, 60),   // Offset maximo de posicion (ancho y profundidad del cuadrado)
		MVector3(0, -25, 0),    // Velocidad
		MVector3(0, -2, 0),     // Offset minimo de la velocidad 
		MVector3(0, 0, 0),      // Offset maximo de la velocidad a
		MVector3(0, 0, 0),      // Aceleracion
		MVector3(0, 0, 0),      // Offset minimo de la aceleracion
		MVector3(0, 0, 0),      // Offset maximo de la maxima
		1,                  // Tiempo de vida minimo
		2,                  // Tiempo de vida maximo
		50.0,                 // Distancia maxima
		true,                 // Activo
		50,						//masa
		Vector4(0.6, 0.7, 1.0, 1) // Color azul
	);
	pG2->addForceGenerator(gG);
	myPS->addParticleGen(pG2);

	//humo
	// Generador de humo
	pG2 = new uniformGeneratorWithForces(
		200,                     // Maximo de particulas
		0.05,                    // Tiempo entre emisiones
		mVector3D(30, 30, 30),   // Posicion
		mVector3D(-5, -5, -5),   // Offset minimo de posicion (cubo alrededor del centro)
		mVector3D(5, 5, 5),      // Offset maximo de posicion
		mVector3D(0, 0, 0),      // Velocidad 
		mVector3D(-3, -13, -3),   // Offset minimo de velocidad (hacia todas direcciones)
		mVector3D(3, 13, 3),      // Offset maximo de velocidad
		mVector3D(0, -10, 0),      // Aceleracion
		mVector3D(0, 0, 0),      // Offset minimo de aceleracion
		mVector3D(0, 0, 0),      // Offset maximo de aceleracion
		4,                        // Tiempo de vida minimo
		4,                        // Tiempo de vida maximo
		10,                       // Distancia maxima
		true,                     // Activo
		50,							//masa
		Vector4(0.5, 0.5, 0.5, 1) // Color gris
	);
	pG2->addForceGenerator(vG);
	myPS->addParticleGen(pG2);
}

void myScene::scene5()
{
	ParticleWithMass* pstatic = new ParticleWithMass({ 10.0,0.0,0.0, }, { 0.0,0.0,0.0 }, { 0.0,0.0,0.0 }, 0.4, 0, 1000, 2);
	ParticleWithMass* pstring = new ParticleWithMass({ 10.0,-10.0,0.0, }, { 0.0,0.0,0.0 }, { 0.0,0.0,0.0 }, 0.4,0.2, 1000, 2);
	ParticleWithMass* pstring2 = new ParticleWithMass({ 10.0,-20.0,0.0, }, { 0.0,0.0,0.0 }, { 0.0,0.0,0.0 }, 0.4, 0.2, 1000, 2);

	gravityForceGenerator* gG = new gravityForceGenerator(mVector3D(0, -500, 0));
	pstring->addForceGenerator(gG);

	SpringForceGenerator* string = new SpringForceGenerator(1, 5, pstatic);
	pstring->addForceGenerator(string);

	SpringForceGenerator* string2 = new SpringForceGenerator(1, 5, pstring);
	pstring->addForceGenerator(string2);


	mFG.emplace("string", string);
	mParticles.push_back(pstring);
	mParticles.push_back(pstatic);

	mFG.emplace("gravity", gG);
}

void myScene::scene6()
{
	ParticleWithMass* p = new ParticleWithMass({ 0.0,0.0,0.0, }, { 0.0,0.0,0.0 }, { 0.0,0.0,0.0 }, 0.4,10000000, 1000, 3);
	//ParticleWithMass* p = new ParticleWithMass({ 0.0,0.0,0.0, }, { 0.0,0.0,0.0 }, { 0.0,0.0,0.0 }, 0.4, 10000, 1000, 3
	//ParticleWithMass* p = new ParticleWithMass({ 0.0,0.0,0.0, }, { 0.0,0.0,0.0 }, { 0.0,0.0,0.0 }, 0.4, 200, 1000, 3);
	ParticleWithMass* p2 = new ParticleWithMass({ 0.0,0.0,0.0, }, { 0.0,0.0,0.0 }, { 0.0,0.0,0.0 }, 50, 0, 1000, 3,CreateShape(physx::PxBoxGeometry(3,3,3)),Vector4(0.0,0.0,0.7,0.2));

	BouyancyForceGenerator* bFG = new BouyancyForceGenerator(3, 3, 1000,p2);
	//gravityForceGenerator* gG = new gravityForceGenerator(mVector3D(0, -10, 0));
	p->addForceGenerator(bFG);
	//p->addForceGenerator(gG);

	mParticles.push_back(p);
	mFG.emplace("bouyancy", bFG);
	//mFG.emplace("gravity", gG);
}

void myScene::scene7()
{
	SolidStatic* suelo = new SolidStatic(gScene, gPhysics, CreateShape(PxBoxGeometry(500, 5, 500)),PxTransform(0,0,0),Vector4(1,1,0,1));
	mSolidsStatics.push_back(suelo);

	SolidDynamic* coche = new SolidDynamic(gScene, gPhysics,
		CreateShape(PxBoxGeometry(10, 5, 10)), PxTransform(0, 0, 0), 0.15,10,10,10, Vector4(1, 0, 1, 1));

	mSolidDynamics.push_back(coche);
}

void myScene::scene8()
{
	SolidSystem* mSolSys = new SolidSystem;
	mSSystems.emplace("system", mSolSys);
	UniformSolidGenerator* rain = new UniformSolidGenerator(
		gScene,
		gPhysics,
		5000,                  // maxParticles
		0.07,                  // emisionVel
		Vector3(0, 500, 0),   // genPos

		// Posición aleatoria
		Vector3(-500, 0, -500), // genPosOffsetMin
		Vector3(500, 5, 500),   // genPosOffsetMax

		// Velocidad
		Vector3(0, -30, 0),      // genVel
		Vector3(-1, -5, -1),     // genVelOffsetMin
		Vector3(1, 0, 1),        // genVelOffsetMax

		// Velocidad angular
		Vector3(0, 0, 0),        // genAngVel
		Vector3(0, 0, 0),        // genAngVelOffsetMin
		Vector3(0, 0, 0),        // genAngVelOffsetMax

		// Material
		0.0, 0.0, 0.05,          // staticFrictionMin, dynamicFrictionMin, restitutionMin
		0.0, 0.0, 0.05,          // staticFrictionMax, dynamicFrictionMax, restitutionMax

		// Vida
		4.0, 6.0,                // timeLifeMin, timeLifeMax

		// Distancia máxima
		1000.0,                  // maxDistance

		true,                     // active
		1000.0f,                  // density

		CreateShape(PxSphereGeometry(3.0)),              // PxShape*
		Vector4(0.5, 0.5, 1.0, 1.0) // color
	);

	NormalSolidGenerator* hose = new NormalSolidGenerator(
		0.0, 0.0,           // media, desviacion (casi cero para evitar error)
		gScene,
		gPhysics,
		2000,                   // maxParticles
		0.2,                  // emisionVel
		Vector3(0, 1.2f, 0),    // genPos (boquilla)
		Vector3(0, 0, 0),       // genPosOffset (sin variacion)
		Vector3(0, 0, 40),      // genVel (direccion fija)
		Vector3(0, 0, 0),       // genVelOffset (sin variacion)
		Vector3(0, 0, 0),       // genAngVel
		Vector3(0, 0, 0),       // genAngVelOffset
		0.0, 0.0, 0.05,         // staticFrictionMin, dynamicFrictionMin, restitutionMin
		0.0, 0.0, 0.05,         // staticFrictionMax, dynamicFrictionMax, restitutionMax
		1.5, 2.5,               // timeLifeMin, timeLifeMax
		100.0,                  // maxDistance
		true,                   // active
		1000.0f,                // density (agua)
		CreateShape(PxSphereGeometry(3)),  // shape
		Vector4(0.4f, 0.6f, 1.0f, 1.0f)                          // color
	);



	mSolSys->addSolidGenerator(rain);
	mSolSys->addSolidGenerator(hose);
}

void myScene::scene9()
{
	SolidSystem* mSolSys = new SolidSystem;
	mSSystems.emplace("system", mSolSys);
	NormalSolidGenerator* hose = new NormalSolidGenerator(
		0.0, 0.0,           // media, desviacion (casi cero para evitar error)
		gScene,
		gPhysics,
		2000,                   // maxParticles
		0.2,                  // emisionVel
		Vector3(0, 1.2f, 0),    // genPos (boquilla)
		Vector3(0, 0, 0),       // genPosOffset (sin variacion)
		Vector3(0, 0, 40),      // genVel (direccion fija)
		Vector3(0, 0, 0),       // genVelOffset (sin variacion)
		Vector3(0, 0, 0),       // genAngVel
		Vector3(0, 0, 0),       // genAngVelOffset
		0.0, 0.0, 0.05,         // staticFrictionMin, dynamicFrictionMin, restitutionMin
		0.0, 0.0, 0.05,         // staticFrictionMax, dynamicFrictionMax, restitutionMax
		1.5, 2.5,               // timeLifeMin, timeLifeMax
		100.0,                  // maxDistance
		true,                   // active
		1000.0f,                // density (agua)
		CreateShape(PxSphereGeometry(3)),  // shape
		Vector4(0.4f, 0.6f, 1.0f, 1.0f)                          // color
	);

	WindForceGenerator* wG = new WindForceGenerator(mVector3D(0.0f, 1500.0f, 0.0f), 0.8f);
	hose->addForceGenerator(wG);

	mSolSys->addSolidGenerator(hose);
}

void myScene::GameScene()
{
	SolidStatic* suelo = new SolidStatic(gScene, gPhysics, CreateShape(PxBoxGeometry(200, 5, 200)), PxTransform(0, 0, 0), Vector4(1, 1, 0, 1));
	mSolidsStatics.push_back(suelo);

	SolidStatic* pared1 = new SolidStatic(gScene, gPhysics, CreateShape(PxBoxGeometry(200, 200, 5)), PxTransform(0, 0, 200), Vector4(1, 1, 0, 1));
	mSolidsStatics.push_back(pared1);

	SolidStatic* pared2 = new SolidStatic(gScene, gPhysics, CreateShape(PxBoxGeometry(200, 200, 5)), PxTransform(0, 0, -200), Vector4(1, 1, 0, 1));
	mSolidsStatics.push_back(pared2);

	SolidStatic* pared3 = new SolidStatic(gScene, gPhysics, CreateShape(PxBoxGeometry(5, 200, 200)), PxTransform(200, 0, 0), Vector4(1, 1, 0, 1));
	mSolidsStatics.push_back(pared3);

	SolidStatic* pared4 = new SolidStatic(gScene, gPhysics, CreateShape(PxBoxGeometry(5, 200, 200)), PxTransform(-200, 0, 0), Vector4(1, 1, 0, 1));
	mSolidsStatics.push_back(pared4);

	configureCar();

	createNewBall();

	createGoalP1();

	createParticleSystemInGame();

	createStringMarker();
}

void myScene::PoyectoIntermedioScene()
{
	gravityForceGenerator* gG = new gravityForceGenerator(mVector3D(0, -9.8, 0));
	WindForceGenerator* wG = new WindForceGenerator(mVector3D(5, 5, 0), 0.8f);
	VortexForceGenerator* vG = new VortexForceGenerator(mVector3D(30, 30, 30), 0.02, 0.1, 2);
	mFG.emplace("gravedad", gG);
	mFG.emplace("viento", wG);
	mFG.emplace("vortex", vG);

	ParticleSystem* myPS = new ParticleSystem();
	mPSystems.emplace("fuegoCoche", myPS);
	//fuego
	NormalGeneratorWithForces* pG = new NormalGeneratorWithForces(
		300, 0.003,                      // numero particulas, velocidad de emision
		mVector3D(0, 0, 0),             // Posicion
		mVector3D(1, 0.5, 1),           // Offset de la posicion
		mVector3D(0, 0, 8),             // velocidad
		mVector3D(2, 3, 2),             // Offset de la velocidad
		MVector3(0, 0, 2),              // aceleracion
		MVector3(0, 0, 1),              // Offset de la aceleracion
		1, 3, 60,                       // vida minia, maxima y distancia
		true,							// Active
		0.0, 0.4,                       // media y desviacion
		50,								//masa
		Vector4(1, 0.5, 0, 1)           // color
	);
	myPS->addParticleGen(pG);
	myPS->setActive(false);
	//mCar = new Car(MVector3(0, 0, 0), MVector3(0, 0, 0), 40, 0.5, 30, -1, 5, 3, 4, Vector4(0.0, 0.0, 1.0, 1.0));
	pG->addForceGenerator(wG);
	mCar->setPS(myPS);
	//mParticles.push_back(mCar);
}

void myScene::configureCar()
{
	// Crear geometría y material
	PxBoxGeometry carGeom(2.0f, 1.0f, 4.0f);  // ancho, alto, largo
	PxMaterial* carMaterial = gPhysics->createMaterial(0.6f, 0.4f, 0.1f); // staticFric, dynFric, restitution
	PxShape* carShape = gPhysics->createShape(carGeom, *carMaterial);

	// Transform inicial (posición y orientación)
	PxTransform startTransform(PxVec3(0, 6.1f, 0), PxQuat(PxIdentity));

	// Color del coche
	Vector4 carColor(0.8f, 0.0f, 0.0f, 1.0f); // rojo

	// Crear el coche
	double density = 1200.0;
	double speed = 8000.0;
	double maxSpeed = 9000.0;
	double damping = 0.5;
	double jumpForce = 16000;
	double highHeight = 30;

	mCar = new Car(gScene,gPhysics,carShape,startTransform,density,0.1,0.1,0.1,speed,maxSpeed,damping,jumpForce,highHeight,
		carColor);

	NormalGeneratorWithForces* pG = new NormalGeneratorWithForces(
		300, 0.003,                      // numero particulas, velocidad de emision
		mVector3D(0, 0, 0),             // Posicion
		mVector3D(1, 0.5, 1),           // Offset de la posicion
		mVector3D(0, 0, 8),             // velocidad
		mVector3D(2, 3, 2),             // Offset de la velocidad
		MVector3(0, 0, 2),              // aceleracion
		MVector3(0, 0, 1),              // Offset de la aceleracion
		1, 3, 60,                       // vida minia, maxima y distancia
		true,							// Active
		0.0, 0.4,                       // media y desviacion
		50,								//masa
		Vector4(1, 0.5, 0, 1)           // color
	);

	ParticleSystem* myPS = new ParticleSystem();
	myPS->addParticleGen(pG);
	myPS->setActive(false);
	mCar->setPS(myPS);
}

void myScene::createNewBall()
{
	// ---------- CONFIGURACIÓN ----------
	float radius = 10.0f;          // Tamaño de la bola (GIGANTE)
	double density = 10.0;         // Densidad alta → pesada
	float staticFriction = 0.8f;
	float dynamicFriction = 0.6f;
	float restitution = 0.4f;      // Poco rebote
	Vector4 color(0.2f, 0.6f, 1.0f, 1.0f); // Azul

	// ---------- MATERIAL ----------
	PxMaterial* material = gPhysics->createMaterial(
		staticFriction,
		dynamicFriction,
		restitution
	);

	// ---------- SHAPE (ESFERA) ----------
	PxShape* sphereShape = gPhysics->createShape(
		PxSphereGeometry(radius),
		*material
	);

	// ---------- TRANSFORM ----------
	Vector3 pos = Vector3(0, 20, 0);
	PxTransform transform(pos);

	// ---------- OBJETO DINÁMICO ----------
	PxFilterData filter;
	filter.word0 = BALL;
	filter.word1 = DEFAULT | GOAL;

	mBall = new Ball(gScene,gPhysics,sphereShape,transform,density,staticFriction,dynamicFriction,restitution,filter,color);

	mBall->getObject()->setMass(500.0f);              // Muy pesada
	mBall->getObject()->setLinearDamping(0.02f);      // Que ruede bien
	mBall->getObject()->setAngularDamping(0.05f);
}

void myScene::createGoalP1()
{

	PxFilterData filter;
	filter.word0 = GOAL;
	filter.word1 = DEFAULT | BALL;
	g1 = new Goal(gScene, gPhysics, CreateShape(PxBoxGeometry(5, 30, 50)),
		PxTransform(Vector3(-180, 0, 0)), filter, Vector4(1, 0, 0, 1));
}

void myScene::resetBall()
{
	//if (mBall != nullptr) {
		//delete mBall;
		//mBall = nullptr;
	//}

	//createNewBall();
	mBall->getObject()->setGlobalPose(PxTransform(0,40,0));
	destroyBall = false;
}

void myScene::createStringMarker()
{
	SolidDynamic* marker = new SolidDynamic(gScene, gPhysics, CreateShape(PxBoxGeometry(20, 20, 5)), PxTransform(0, 100, 180),0.001,5.0,
		5.0,0.0,Vector4(1, 0.5, 0, 1));
	mSolidDynamics.push_back(marker);

	marker->getObject()->setRigidDynamicLockFlags(
		PxRigidDynamicLockFlag::eLOCK_LINEAR_X |PxRigidDynamicLockFlag::eLOCK_LINEAR_Z | PxRigidDynamicLockFlag::eLOCK_ANGULAR_X |
		PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y |PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z);


	ParticleWithMass* pstatic = new ParticleWithMass(mVector3D(marker->getPos().x, marker->getPos().y, marker->getPos().z) + mVector3D(0.0, 50, 0.0),
		{0.0,0.0,0.0}, {0.0,0.0,0.0}, 0.4, 0, 1000, 2);
	mParticles.push_back(pstatic);

	SpringForceGenerator* string = new SpringForceGenerator(150, 1, pstatic);
	marker->addForceGenerator(string);


	mFG.emplace("muelleMarker", string);
}

void myScene::toggleTurbo()
{
	mCar->setPSActive(!mCar->isPSActive());
}

void myScene::iniLLuvia()
{
	ParticleSystem* myPS = new ParticleSystem();
	mPSystems.emplace("lluvia", myPS);
	// Generador de lluvia
	uniformGeneratorWithForces* pG = new uniformGeneratorWithForces(
		100,                  // Ma ximo de particulas
		0.07,                 // Tiempo entre emisiones
		mVector3D(0, 100, 0),    // Posicion del generador (altura)
		MVector3(-60, 0, -60),      // Offset minimo de posicion
		mVector3D(60, 0, 60),   // Offset maximo de posicion (ancho y profundidad del cuadrado)
		MVector3(0.0, -40, 0.0),    // Velocidad
		MVector3(0.0, -40, 0.0),     // Offset minimo de la velocidad 
		MVector3(0, 0, 0),      // Offset maximo de la velocidad a
		MVector3(0, 0, 0),      // Aceleracion
		MVector3(0, 0, 0),      // Offset minimo de la aceleracion
		MVector3(0, 0, 0),      // Offset maximo de la maxima
		1,                  // Tiempo de vida minimo
		2,                  // Tiempo de vida maximo
		50.0,                 // Distancia maxima
		true,                 // Activo
		0.0,						//masa
		Vector4(0.6, 0.7, 1.0, 1) // Color azul
	);
	if (mFG.count("gravedad")) {
		pG->addForceGenerator(mFG.at("gravedad"));
		mFG.at("gravedad")->setActive(false);
	}
	if (mFG.count("viento")) {
		pG->addForceGenerator(mFG.at("viento"));
		mFG.at("viento")->setActive(false);
	}

	myPS->addParticleGen(pG);
}

void myScene::stopMPSystems(std::string s)
{
	if (mPSystems.count(s))
		mPSystems[s]->setActive(!mPSystems[s]->getActive());
}

void myScene::toggleMFG(std::string s)
{
	if (mFG.count(s))
		mFG[s]->setActive(!mFG[s]->getActive());
}

void myScene::goal()
{
	destroyBall = true;
	fuegoG1->setActive(true);
	hoseG1->setActive(true);
	timeParts = 0;
	isGoal = true;
}

void myScene::createParticleSystemInGame()
{
	fuegoG1 = new ParticleSystem();

	Vector3D pos(g1->getObj()->getGlobalPose().p.x, g1->getObj()->getGlobalPose().p.y,
		g1->getObj()->getGlobalPose().p.z);

	WindForceGenerator* wG = new WindForceGenerator(mVector3D(500, 500, 0), 0.8f);
	VortexForceGenerator* vG = new VortexForceGenerator(mVector3D(30, 30, 30), 30, 10, 30);

	mFG.emplace("viento", wG);
	mFG.emplace("vortex", vG);

	//fuego
	NormalGeneratorWithForces* pG = new NormalGeneratorWithForces(
		300, 0.003,                      // numero particulas, velocidad de emision
		mVector3D(pos + MVector3(30, 40,0)),					// Posicion
		mVector3D(0,0,0),				// Offset de la posicion
		mVector3D(0, 8, 0),             // velocidad
		mVector3D(0.2, 3, 0.2),             // Offset de la velocidad
		MVector3(0, 2, 0),              // aceleracion
		MVector3(0, 1, 0),              // Offset de la aceleracion
		1, 3, 60,                       // vida minia, maxima y distancia
		true,							// Active
		0.0, 0.4,                       // media y desviacion
		0.0,								//masa
		Vector4(1, 0.5, 0, 1)           // color
	);

	pG->addForceGenerator(wG);
	pG->addForceGenerator(vG);
	fuegoG1->addParticleGen(pG);
	mPSystems.emplace("fuego", fuegoG1);
	fuegoG1->setActive(false);

	hoseG1 = new SolidSystem();

	NormalSolidGenerator* hose = new NormalSolidGenerator(
		0.0, 0.0,           // media, desviacion (casi cero para evitar error)
		gScene,
		gPhysics,
		2000,                   // maxParticles
		0.2,                  // emisionVel
		Vector3(pos.toVector3() + MVector3(30, 40, 0).toVector3()),    // genPos (boquilla)
		Vector3(0, 0, 0),       // genPosOffset (sin variacion)
		Vector3(40, 10, 0),      // genVel (direccion fija)
		Vector3(0, 0, 0),       // genVelOffset (sin variacion)
		Vector3(0, 0, 0),       // genAngVel
		Vector3(0, 0, 0),       // genAngVelOffset
		0.0, 0.0, 0.05,         // staticFrictionMin, dynamicFrictionMin, restitutionMin
		0.0, 0.0, 0.05,         // staticFrictionMax, dynamicFrictionMax, restitutionMax
		1.5, 2.5,               // timeLifeMin, timeLifeMax
		100.0,                  // maxDistance
		true,                   // active
		1000.0f,                // density (agua)
		CreateShape(PxSphereGeometry(3)),  // shape
		Vector4(0.4f, 0.6f, 1.0f, 1.0f)                          // color
	);


	hoseG1->addSolidGenerator(hose);
	mSSystems.emplace("hoseG1", hoseG1);
	hoseG1->setActive(false);


	
	//EL OTRO SISTEMA DE PARTICULAS REQUERIDO SE INICIA PULSANDO LA L Y SE PUEDE PAUSAR O REANUDAR CON LA K ES EL DE LLUVIA
	//SE CREA EN INILLUVIA
}
