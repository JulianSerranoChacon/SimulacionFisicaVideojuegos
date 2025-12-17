#pragma once

#include <list>
#include "SolidGenerator.h"

class SolidSystem
{
public:
	SolidSystem();
	~SolidSystem();

	void addSolidGenerator(SolidGenerator* sG);
	void removeSolidGenerator(SolidGenerator* sG);
	//TODO
	void update(double t);
	//TODO
	void setActive(bool a);
	inline bool getActive() { return active; }

private:
	std::list<SolidGenerator*> mSG;
	bool active = true;
};

