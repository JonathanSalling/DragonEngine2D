#pragma once
#include <vector>

namespace DragonEngine
{
	class Collider;

	class CollisionSystem
	{
	public:
		static bool Check(const Collider& aCollider, const Collider& aOtherCollider);
	};
}


