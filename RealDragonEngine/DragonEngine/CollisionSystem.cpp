#include "CollisionSystem.h"
#include "Collider.h"

bool DragonEngine::CollisionSystem::Check(std::vector<DragonEngine::Collider*>& colliders)
{
	for (size_t i = 0; i < colliders.size(); i++)
	{
		for (size_t j = i + 1; j < colliders.size(); j++)
		{
			if (colliders[i]->Intersects(*colliders[j]))
			{
				return true;
				// TEMP: just notify
				//colliders[i]->OnCollision(*colliders[j]);
				//colliders[j]->OnCollision(*colliders[i]);
			}
		}
	}
	return false;
}

bool DragonEngine::CollisionSystem::Check(std::vector<Collider*>& someColliders, std::vector<Collider*>& someOtherColliders)
{
	for (Collider* colliderA : someColliders)
	{
		for (Collider* colliderB : someOtherColliders)
		{
			if (colliderA->Intersects(*colliderB))
			{
				return true;
				// TEMP: just notify
				//colliderA->OnCollision(*colliderB);
				//colliderB->OnCollision(*colliderA);
			}
		}
	}
	return false;
}

bool DragonEngine::CollisionSystem::Check(const Collider& aCollider, const Collider& aOtherCollider)
{
	if (aCollider.Intersects(aOtherCollider))
	{
		return true;
		// TEMP: just notify
		//a.OnCollision(b);
		//b.OnCollision(a);
	}
	return false;
}
