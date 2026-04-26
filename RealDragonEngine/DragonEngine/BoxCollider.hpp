#pragma once
#include "Vector2.hpp"
#include "Collider.h"
#include <cmath>
#include "TemplateUtilities.h"
#include "SphereCollider.hpp"

namespace DragonEngine
{
	class BoxCollider : public Collider
	{
	public:
		BoxCollider();
		BoxCollider(const BoxCollider& aBoxCollider);
		BoxCollider(const Vector2f& aCenter, const Vector2f& aHalfSize);
		void Set(const Vector2f& aCenter, const Vector2f& aHalfSize);
		bool IsInside(const Vector2f& aPosition) const;

		bool Intersects(const Collider& other) const;
		bool Intersects(const BoxCollider& other) const;
		bool Intersects(const SphereCollider& other) const;

		Vector2f GetCenter() const;
		Vector2f GetHalfSize() const;
		ColliderType GetType() const override { return ColliderType::Box; }
	private:
		Vector2f myCenter;
		Vector2f myHalfSize;
	};

	BoxCollider::BoxCollider() : myCenter{ 0, 0 }, myHalfSize{ 0, 0 }
	{
	}

	BoxCollider::BoxCollider(const BoxCollider& aBoxCollider)
		: myCenter(aBoxCollider.myCenter), myHalfSize(aBoxCollider.myHalfSize)
	{
	}

	BoxCollider::BoxCollider(const Vector2f& aCenter, const Vector2f& aHalfSize)
		: myCenter(aCenter), myHalfSize(aHalfSize)
	{
	}

	void BoxCollider::Set(const Vector2f& aCenter, const Vector2f& aHalfSize)
	{
		myCenter = aCenter;
		myHalfSize = aHalfSize;
	}

	bool BoxCollider::IsInside(const Vector2f& aPosition) const
	{
		return std::abs(aPosition.x - myCenter.x) <= myHalfSize.x &&
			std::abs(aPosition.y - myCenter.y) <= myHalfSize.y;
	}

	inline bool BoxCollider::Intersects(const Collider& other) const
	{
		return other.Intersects(*this);
	}

	inline bool BoxCollider::Intersects(const BoxCollider& aBoxCollider) const
	{
		return std::abs(myCenter.x - aBoxCollider.myCenter.x) <= (myHalfSize.x + aBoxCollider.myHalfSize.x) &&
			std::abs(myCenter.y - aBoxCollider.myCenter.y) <= (myHalfSize.y + aBoxCollider.myHalfSize.y);
	}

	inline bool BoxCollider::Intersects(const SphereCollider& aSphereCollider) const
	{
		Vector2f min = { myCenter.x - myHalfSize.x, myCenter.y - myHalfSize.y };

		Vector2f max = { myCenter.x + myHalfSize.x, myCenter.y + myHalfSize.y };

		Vector2f closest = Clamp(aSphereCollider.GetCenter(), min, max);

		float dx = aSphereCollider.GetCenter().x - closest.x;
		float dy = aSphereCollider.GetCenter().y - closest.y;

		float distSq = dx * dx + dy * dy;

		return distSq <= aSphereCollider.GetRadius() * aSphereCollider.GetRadius();
	}

	inline Vector2f BoxCollider::GetCenter() const
	{
		return myCenter;
	}

	inline Vector2f BoxCollider::GetHalfSize() const
	{
		return myHalfSize;
	}
}