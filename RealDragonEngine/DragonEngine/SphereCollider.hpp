#pragma once
#include "Vector2.hpp"
#include "Collider.h"
#include "BoxCollider.hpp"

namespace DragonEngine
{
	class SphereCollider : public Collider
	{
	public:
		SphereCollider();
		SphereCollider(const SphereCollider& aSphere);
		SphereCollider(const Vector2f& aCenter, float aRadius);

		bool IsInside(const Vector2f& aPosition) const;
		bool Intersects(const BoxCollider& other) const override;
		bool Intersects(const SphereCollider& other) const override;

		Vector2f GetCenter() const;
		float GetRadius() const;
		ColliderType GetType() const override;

	private:
		Vector2f myCenter;
		float myRadius;

	};

	SphereCollider::SphereCollider() : myCenter{ 0,0 }, myRadius(0)
	{
	}

	SphereCollider::SphereCollider(const SphereCollider& aSphere)
		: myCenter(aSphere.myCenter), myRadius(aSphere.myRadius)
	{
	}

	SphereCollider::SphereCollider(const Vector2f& aCenter, float aRadius)
		: myCenter(aCenter), myRadius(aRadius)
	{
	}

	bool SphereCollider::IsInside(const Vector2f& aPosition) const
	{
		Vector2f distance = aPosition - myCenter;
		return distance.LengthSqr() <= (myRadius * myRadius);
	}

	float SphereCollider::GetRadius() const
	{
		return myRadius;
	}

	ColliderType SphereCollider::GetType() const
	{
		return ColliderType::Sphere;
	}

	inline bool SphereCollider::Intersects(const BoxCollider& other) const
	{
		return other.Intersects(*this);
	}

	inline bool SphereCollider::Intersects(const SphereCollider& other) const
	{
		Vector2f distance = other.GetCenter() - myCenter;
		float radius = myRadius + other.GetRadius();

		return distance.LengthSqr() <= (radius * radius);
	}

	Vector2f SphereCollider::GetCenter() const
	{
		return myCenter;
	}
}