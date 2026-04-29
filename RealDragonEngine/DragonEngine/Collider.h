#pragma once
#include <string>
#include "Vector.h"

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

		// Get the type of the collider (Box, Sphere, etc.)
		virtual ColliderType GetType() const = 0;

		// Check if a collider is intersecting with this collider
		virtual bool Intersects(const Collider& aOther) const = 0;

		// Draw the collider for debugging purposes
		virtual void DebugDraw() const = 0;

		// Enable or disable the collider for collision detection
		void SetEnabled(bool aEnabled);
		// Check if the collider is currently enabled for collision detection
		bool IsEnabled() const;

		// Check if a position is inside the collider
		virtual bool IsInside(const Vector2f& aPosition) const = 0;

	protected:
		Collider();
		bool myEnabled = true; // Whether the collider is active for collision detection

		// Get the type name of the collider (BoxCollider, SphereCollider, etc.)
		virtual const char* GetTypeName() const = 0;

	private:
		static int sNextId;
		int myId;
		std::string myName; // For debugging purposes, to identify colliders in logs
	};
}

