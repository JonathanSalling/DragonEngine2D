#pragma once
#include <vector>

namespace DragonEngine
{
	class Collider;

	class CollisionSystem
	{
	public:
		static void Check(std::vector<Collider*>& colliders);
	};
}


