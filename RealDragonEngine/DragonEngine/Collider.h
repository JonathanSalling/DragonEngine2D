#pragma once
#include <string>
//#include "BoxCollider.hpp"
//#include "Sphere.hpp"

namespace DragonEngine
{
	class BoxCollider;
	class SphereCollider;
}

namespace DragonEngine
{
	enum class ColliderType
	{
		Box,
		Sphere
	};

	class Collider
	{
	public:
		virtual ~Collider() = default;

		// Set a custom name for the collider, useful for debugging and logging purposes
		void SetName(const std::string& aName);
		// Get the name of the collider, useful for debugging and logging purposes
		std::string GetName() const;

		virtual ColliderType GetType() const = 0;

		virtual bool Intersects(const Collider& aOther) const = 0;
		virtual bool Intersects(const BoxCollider& aOther) const = 0;
		virtual bool Intersects(const SphereCollider& aOther) const = 0;

	private:
		Collider();
		int GenerateUniqueId();
		static int sNextId;
		int myId;
		std::string myName; // For debugging purposes, to identify colliders in logs
	};
}

