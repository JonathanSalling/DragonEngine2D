#pragma once
#include <string>

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
		// Get the type name of the collider (BoxCollider, SphereCollider, etc.)
		virtual const char* GetTypeName() const = 0;

		// Check if a collider is intersecting with this collider
		virtual bool Intersects(const Collider& aOther) const = 0;

		// Draw the collider for debugging purposes
		virtual void DebugDraw() const = 0;

		// Enable or disable the collider for collision detection
		void SetEnabled(bool aEnabled);
		// Check if the collider is currently enabled for collision detection
		bool IsEnabled() const;

	protected:
		Collider();
		bool myEnabled = true; // Whether the collider is active for collision detection

	private:
		int GenerateUniqueId();
		static int sNextId;
		int myId;
		std::string myName; // For debugging purposes, to identify colliders in logs
	};
}

