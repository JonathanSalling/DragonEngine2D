#pragma once
#include <vector>

namespace DragonEngine
{
	class Collider;

	class CollisionSystem
	{
	public:
		static bool Check(std::vector<Collider*>& someColliders);
		static bool Check(std::vector<Collider*>& someColliders, std::vector<Collider*>& someOtherColliders);
		static bool Check(const Collider& aCollider, const Collider& aOtherCollider);
	};
}


