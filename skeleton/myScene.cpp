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

using namespace physx;

myScene::myScene()
{
	chooseScene(4);
	//gameScene();
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
	for (auto e : mPSystems) 
	{
		if (e.second != nullptr)
			delete e.second;
		e.second = nullptr;
	}
	for (auto e : mFG)
	{
		if (e.second != nullptr)
			delete e.second;
		e.second = nullptr;
	}
}

void myScene::update(float t)
{
	for (int i = 0; i < mParticles.size(); i++)
		if (mParticles[i] != nullptr)
			mParticles[i]->integrate(t);

	for (auto pS : mPSystems)
		pS.second->update(t);
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

	createAxis();
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
	ParticleWithMass* pstring = new ParticleWithMass({ 10.0,-100.0,0.0, }, { 0.0,0.0,0.0 }, { 0.0,0.0,0.0 }, 0.4,0.2, 1000, 2);

	gravityForceGenerator* gG = new gravityForceGenerator(mVector3D(0, -10, 0));
	pstring->addForceGenerator(gG);

	SpringForceGenerator* string = new SpringForceGenerator(1, 10, pstatic);
	pstring->addForceGenerator(string);


	mFG.emplace("string", string);
	mParticles.push_back(pstring);
	mParticles.push_back(pstatic);
}

void myScene::gameScene()
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
	mCar = new Car(MVector3(0, 0, 0), MVector3(0, 0, 0), 40, 0.5, 30, -1, 5, 3, 4, Vector4(0.0, 0.0, 1.0, 1.0));
	pG->addForceGenerator(wG);
	mCar->setPS(myPS);
	mParticles.push_back(mCar);
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
