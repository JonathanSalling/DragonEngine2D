#pragma once
#include "Vector2.hpp"
#include "Collider.h"

namespace DragonEngine
{
	class SphereCollider : public Collider
	{
	public:
		SphereCollider();
		SphereCollider(const SphereCollider& aSphere);
		SphereCollider(const Vector2f& aCenter, float aRadius);

		bool IsInside(const Vector2f& aPosition) const;
		bool Intersects(const Collider& other) const override;

		Vector2f GetCenter() const;
		void SetCenter(const Vector2f& aCenter);
		float GetRadius() const;
		void SetRadius(float aRadius);

		ColliderType GetType() const override;
		const char* GetTypeName() const { return "SphereCollider"; }
		void DebugDraw() const override;

	private:
		bool IntersectsBox(const BoxCollider& other) const;
		bool IntersectsSphere(const SphereCollider& other) const;

		Vector2f myCenter;
		float myRadius;

	};
}