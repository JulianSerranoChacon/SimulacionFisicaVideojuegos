#include "CollisionManager.h"

CollisionManager::CollisionManager(myScene* mScene): mScene(mScene)
{
}

void CollisionManager::onContact(PxContactPairHeader const& pairHeader, PxContactPair const* pairs, PxU32 nbPairs)
{
	for (PxU32 i = 0; i < nbPairs; i++) {
		const PxContactPair& pair = pairs[i];

		PxShape* s1 = pair.shapes[0];
		PxShape* s2 = pair.shapes[1];


		PxFilterData filter1 = s1->getSimulationFilterData();
		PxFilterData filter2 = s2->getSimulationFilterData();

		if (filter1.word0 != 0 && filter2.word0 != 0) {
			mScene->goal();
		}
	}
}
