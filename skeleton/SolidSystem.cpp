#include "SolidSystem.h"

SolidSystem::SolidSystem()
{
	mSG = std::list<SolidGenerator*>();
}

SolidSystem::~SolidSystem()
{
	for (SolidGenerator* sg: mSG) {
		delete sg;
		sg = nullptr;
	}
	mSG.clear();
}

void SolidSystem::addSolidGenerator(SolidGenerator* sG)
{
	mSG.push_back(sG);
}

void SolidSystem::removeSolidGenerator(SolidGenerator* sG)
{
	mSG.remove(sG);
	delete sG;
	sG = nullptr;
}

void SolidSystem::update(double t) 
{
	for (SolidGenerator* sg : mSG) {
		sg->update(t);
	}
}

void SolidSystem::setActive(bool a) 
{
	active = a;
	for (SolidGenerator* sg : mSG) {
		if (sg != nullptr)
			sg->setActive(active);
	}
}
