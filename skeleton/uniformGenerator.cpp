#include "uniformGenerator.h"
#include "ParticleGen.h"

uniformGenerator::uniformGenerator(int maxParticles, double emisionVel, mVector3D genPos, mVector3D genPosOffsetMin,
	mVector3D genPosOffsetMax, mVector3D genVel, mVector3D genVelOffsetMin, mVector3D genVelOffsetMax,
	mVector3D genAccel, mVector3D genAccelOffsetMin, mVector3D genAccelOffsetMax,
	double timeLifeMin, double timeLifeMax, double maxDistance, bool active, Vector4 sV) :
	ParticleGenerator(maxParticles, emisionVel, genPos, genPosOffsetMax, genVel, genVelOffsetMax, genAccel, genAccelOffsetMax, timeLifeMin, timeLifeMax, maxDistance, active,sV),
	genPosOffsetMin(genPosOffsetMin),genVelOffsetMin(genVelOffsetMin),genAccelOffsetMin(genAccelOffsetMin)
{
	std::random_device randomDevice;
	random = std::mt19937(randomDevice());
}

void uniformGenerator::generate(double t)
{
	emisionVel -= t;
	if (emisionVel <= 0) {
		emisionVel = iniEmisionVel;
		std::uniform_real_distribution<float> uniformXPos(genPosOffsetMin.getX(), genPosOffset.getX());
		std::uniform_real_distribution<float> uniformYPos(genPosOffsetMin.getY(), genPosOffset.getY());
		std::uniform_real_distribution<float> uniformZPos(genPosOffsetMin.getZ(), genPosOffset.getZ());

		float auxX = uniformXPos(random);
		float auxY = uniformYPos(random);
		float auxZ = uniformZPos(random);
		Vector3D posVar(auxX, auxY, auxZ);
		
		std::uniform_real_distribution<float> uniformXVel(genVelOffsetMin.getX(), genVelOffset.getX());
		std::uniform_real_distribution<float> uniformYVel(genVelOffsetMin.getY(), genVelOffset.getY());
		std::uniform_real_distribution<float> uniformZVel(genVelOffsetMin.getZ(), genVelOffset.getZ());
		auxX = uniformXVel(random);
		auxY = uniformYVel(random);
		auxZ = uniformZVel(random);
		mVector3D velVar(auxX, auxY, auxZ);

		std::uniform_real_distribution<float> uniformXAccel(genAccelOffsetMin.getX(), genAccelOffset.getX());
		std::uniform_real_distribution<float> uniformYAccel(genAccelOffsetMin.getY(), genAccelOffset.getY());
		std::uniform_real_distribution<float> uniformZAccel(genAccelOffsetMin.getZ(), genAccelOffset.getZ());
		auxX = uniformXAccel(random);
		auxY = uniformYAccel(random);
		auxZ = uniformZAccel(random);
		mVector3D accelVar(auxX, auxY, auxZ);

		std::uniform_real_distribution<double> time(timeLifeMin, timeLifeMax);
		listP.push_front(new ParticleGen(genPos + posVar, genVel + velVar, genAccel + accelVar, 0.5, time(random),5.0,sV));
		nParticles++;
	}
}