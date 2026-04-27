#include "CollisionSystem.h"
#include "Collider.h"

bool DragonEngine::CollisionSystem::Check(const Collider& aCollider, const Collider& aOtherCollider)
{
	if (!aCollider.IsEnabled() || !aOtherCollider.IsEnabled())
	{
		return false;
	}

	if (aCollider.Intersects(aOtherCollider))
	{
		return true;
		// TEMP: just notify
		//a.OnCollision(b);
		//b.OnCollision(a);
	}
	return false;
}
