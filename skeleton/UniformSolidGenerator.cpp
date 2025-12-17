#include "UniformSolidGenerator.h"

UniformSolidGenerator::UniformSolidGenerator(PxScene* gScene, PxPhysics* gPhysics,int maxParticles, double emisionVel, Vector3 genPos,
	Vector3 genPosOffsetMin, Vector3 genPosOffsetMax, Vector3 genVel, Vector3 genVelOffsetMin, Vector3 genVelOffsetMax,
	Vector3 genAccel, Vector3 genAccelOffsetMin, Vector3 genAccelOffsetMax, double timeLifeMin, double timeLifeMax,
	double maxDistance, bool active,float density, Vector4 sV):SolidGenerator(gScene,gPhysics,maxParticles,emisionVel,genPos,genPosOffsetMax,
		genVel,genAccelOffsetMax,genAccel,genAccelOffsetMax,timeLifeMin,timeLifeMax,maxDistance,active,sV),genPosOffsetMin(genPosOffsetMin),
	genVelOffsetMin(genVelOffsetMin), genAccelOffsetMin(genAccelOffsetMin), mass(density)
{
	std::random_device randomDevice;
	random = std::mt19937(randomDevice());
}

UniformSolidGenerator::~UniformSolidGenerator()
{
}

void UniformSolidGenerator::generate(double t)
{
	emisionVel -= t;
	if (emisionVel <= 0) {
		emisionVel = iniEmisionVel;
		std::uniform_real_distribution<float> uniformXPos(genPosOffsetMin.x, genPosOffset.x);
		std::uniform_real_distribution<float> uniformYPos(genPosOffsetMin.y, genPosOffset.y);
		std::uniform_real_distribution<float> uniformZPos(genPosOffsetMin.z, genPosOffset.z);

		float auxX = uniformXPos(random);
		float auxY = uniformYPos(random);
		float auxZ = uniformZPos(random);
		Vector3 posVar(auxX, auxY, auxZ);

		std::uniform_real_distribution<float> uniformXVel(genVelOffsetMin.x, genVelOffset.x);
		std::uniform_real_distribution<float> uniformYVel(genVelOffsetMin.y, genVelOffset.y);
		std::uniform_real_distribution<float> uniformZVel(genVelOffsetMin.z, genVelOffset.z);
		auxX = uniformXVel(random);
		auxY = uniformYVel(random);
		auxZ = uniformZVel(random);
		Vector3 velVar(auxX, auxY, auxZ);

		std::uniform_real_distribution<float> uniformXAccel(genAccelOffsetMin.x, genAccelOffset.x);
		std::uniform_real_distribution<float> uniformYAccel(genAccelOffsetMin.y, genAccelOffset.y);
		std::uniform_real_distribution<float> uniformZAccel(genAccelOffsetMin.z, genAccelOffset.z);
		auxX = uniformXAccel(random);
		auxY = uniformYAccel(random);
		auxZ = uniformZAccel(random);
		Vector3 accelVar(auxX, auxY, auxZ);

		std::uniform_real_distribution<double> time(timeLifeMin, timeLifeMax);
		//ParticleWithMass* p = new ParticleWithMass(genPos + posVar, genVel + velVar, genAccel + accelVar, 0.5, mass, time(random), 0.5, sV);
		SolidDynamic* s = new SolidDynamic(gScene,gPhysics,CreateShape(PxSphereGeometry(10)),PxTransform(genPos + posVar),mass);
		

		//for(ForceGenerator* f : fG)
			//s->addForceGenerator(f);

		listS.push_front(s);
		nParticles++;
	}
}
