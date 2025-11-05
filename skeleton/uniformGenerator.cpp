#include "uniformGenerator.h"
#include "ParticleGen.h"

uniformGenerator::uniformGenerator(int maxParticles, double emisionVel, mVector3D genPos, mVector3D genPosOffsetMin,
	mVector3D genPosOffsetMax, mVector3D genVel, mVector3D genVelOffsetMin, mVector3D genVelOffsetMax,
	mVector3D genAccel, mVector3D genAccelOffsetMin, mVector3D genAccelOffsetMax,
	double timeLifeMin, double timeLifeMax, double maxDistance, bool active) :
	ParticleGenerator(maxParticles, emisionVel, genPos, genPosOffset, genVel, genVelOffset, genAccel, genAccelOffset, timeLifeMin, timeLifeMax, maxDistance, active),
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
		std::uniform_real_distribution<float> uniformYPos(genPosOffsetMin.getX(), genPosOffset.getY());
		std::uniform_real_distribution<float> uniformZPos(genPosOffsetMin.getX(), genPosOffset.getZ());

		float auxX = uniformXPos(random);
		float auxY = uniformYPos(random);
		float auxZ = uniformZPos(random);
		mVector3D vAux(auxX, auxY, auxZ);
		mVector3D posVar(genPosOffset.scalar(vAux));
		
		std::uniform_real_distribution<float> uniformXVel(genVelOffsetMin.getX(), genPosOffset.getX());
		std::uniform_real_distribution<float> uniformYVel(genVelOffsetMin.getY(), genPosOffset.getY());
		std::uniform_real_distribution<float> uniformZVel(genVelOffsetMin.getZ(), genPosOffset.getZ());
		auxX = uniformXVel(random);
		auxY = uniformYVel(random);
		auxZ = uniformZVel(random);
		vAux = mVector3D(auxX, auxY, auxZ);
		mVector3D velVar(genVelOffset.scalar(vAux));

		std::uniform_real_distribution<float> uniformXAccel(genAccelOffsetMin.getX(), genAccelOffset.getX());
		std::uniform_real_distribution<float> uniformYAccel(genAccelOffsetMin.getX(), genAccelOffset.getY());
		std::uniform_real_distribution<float> uniformZAccel(genAccelOffsetMin.getX(), genAccelOffset.getZ());
		auxX = uniformXAccel(random);
		auxY = uniformYAccel(random);
		auxZ = uniformZAccel(random);
		vAux = mVector3D(auxX, auxY, auxZ);
		mVector3D accelVar(genAccelOffset.scalar(vAux));

		std::uniform_real_distribution<double> time(timeLifeMin, timeLifeMax);
		listP.push_front(new ParticleGen(genPos + posVar, genVel + velVar, genAccel + accelVar, 0.5, time(random)));
		nParticles++;
	}
}