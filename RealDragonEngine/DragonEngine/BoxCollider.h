#pragma once
#include "Collider.h"
#include "Vector2.hpp"

namespace DragonEngine
{
	class BoxCollider : public Collider
	{
		friend class SphereCollider; // Allow SphereCollider to access private members for intersection tests

	public:
		BoxCollider();
		BoxCollider(const BoxCollider& aBoxCollider);
		BoxCollider(const Vector2f& aCenter, const Vector2f& aHalfSize);

		// Check if a position is inside the box collider
		bool IsInside(const Vector2f& aPosition) const;

		bool Intersects(const Collider& other) const override;

		Vector2f GetCenter() const;
		void SetCenter(const Vector2f& aCenter);
		Vector2f GetHalfSize() const;
		void SetHalfSize(const Vector2f& aHalfSize);

		ColliderType GetType() const override;
		const char* GetTypeName() const override;

		void DebugDraw() const override;

	private:
		bool IntersectsBox(const BoxCollider& other) const;
		bool IntersectsSphere(const SphereCollider& other) const;

		Vector2f myCenter;
		Vector2f myHalfSize;
	};
}