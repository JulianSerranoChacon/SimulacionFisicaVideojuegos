#include "uniformGenerator.h"
#include "ParticleGen.h"

uniformGenerator::uniformGenerator(int maxParticles, double emisionVel, mVector3D genPos, mVector3D genPosOffset, mVector3D genVel, mVector3D genVelOffset,
	mVector3D genAccel, mVector3D genAccelOffset, double timeLifeMin, double timeLifeMax, double maxDistance, bool active, double media, double desviacion) :
	ParticleGenerator(maxParticles, emisionVel, genPos, genPosOffset, genVel, genVelOffset, genAccel, genAccelOffset, timeLifeMin, timeLifeMax, maxDistance, active),
{
	std::random_device randomDevice;
	random = std::mt19937(randomDevice());
}

void uniformGenerator::generate(double t)
{
	emisionVel -= t;
	if (emisionVel <= 0) {
		emisionVel = iniEmisionVel;
		std::uniform_real_distribution<float> uniformXPos(0, genPosOffset.getX());
		std::uniform_real_distribution<float> uniformYPos(0, genPosOffset.getY());
		std::uniform_real_distribution<float> uniformZPos(0, genPosOffset.getZ());

		float auxX = uniformXPos(random);
		float auxY = uniformYPos(random);
		float auxZ = uniformZPos(random);
		mVector3D vAux(auxX, auxY, auxZ);
		mVector3D posVar(genPosOffset.scalar(vAux));
		
		std::uniform_real_distribution<float> uniformXVel(0, genPosOffset.getX());
		std::uniform_real_distribution<float> uniformYVel(0, genPosOffset.getY());
		std::uniform_real_distribution<float> uniformZVel(0, genPosOffset.getZ());
		auxX = uniformXVel(random);
		auxY = uniformYVel(random);
		auxZ = uniformZVel(random);
		vAux = mVector3D(auxX, auxY, auxZ);
		mVector3D velVar(genVelOffset.scalar(vAux));

		std::uniform_real_distribution<float> uniformXAccel(0, genPosOffset.getX());
		std::uniform_real_distribution<float> uniformYAccel(0, genPosOffset.getY());
		std::uniform_real_distribution<float> uniformZAccel(0, genPosOffset.getZ());
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