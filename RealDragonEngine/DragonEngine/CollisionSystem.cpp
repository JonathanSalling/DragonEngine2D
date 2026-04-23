#include "CollisionSystem.h"
#include "Collider.h"

void DragonEngine::CollisionSystem::Check(std::vector<DragonEngine::Collider*>& colliders)
{
	for (size_t i = 0; i < colliders.size(); i++)
	{
		for (size_t j = i + 1; j < colliders.size(); j++)
		{
			if (colliders[i]->Intersects(*colliders[j]))
			{
				// TEMP: just notify
				//colliders[i]->OnCollision(*colliders[j]);
				//colliders[j]->OnCollision(*colliders[i]);
			}
		}
	}
}
