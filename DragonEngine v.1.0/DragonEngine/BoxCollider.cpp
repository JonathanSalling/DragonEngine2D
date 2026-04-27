#include "BoxCollider.h"
#include "Debug.h"
#include "SphereCollider.h"
#include "TemplateUtilities.h"

DragonEngine::BoxCollider::BoxCollider() : myCenter{ 0, 0 }, myHalfSize{ 0.1f, 0.1f }
{
}

DragonEngine::BoxCollider::BoxCollider(const BoxCollider& aBoxCollider)
	: myCenter(aBoxCollider.myCenter), myHalfSize(aBoxCollider.myHalfSize)
{
}

DragonEngine::BoxCollider::BoxCollider(const Vector2f& aCenter, const Vector2f& aHalfSize)
	: myCenter(aCenter), myHalfSize(aHalfSize)
{
}

bool DragonEngine::BoxCollider::IsInside(const Vector2f& aPosition) const
{
	// If the collider is disabled, we consider no position to be inside it
	if (!IsEnabled())
	{
		return false;
	}

	return std::abs(aPosition.x - myCenter.x) <= myHalfSize.x &&
		std::abs(aPosition.y - myCenter.y) <= myHalfSize.y;
}

bool DragonEngine::BoxCollider::Intersects(const Collider& other) const
{
	// If either collider is disabled, they cannot intersect
	if (!IsEnabled() || !other.IsEnabled())
	{
		return false;
	}

	switch (other.GetType())
	{
	case ColliderType::Box:
		return IntersectsBox(static_cast<const BoxCollider&>(other));

	case ColliderType::Sphere:
		return IntersectsSphere(static_cast<const SphereCollider&>(other));
	}

	return false;
}

bool DragonEngine::BoxCollider::IntersectsBox(const BoxCollider& aBoxCollider) const
{
	return std::abs(myCenter.x - aBoxCollider.myCenter.x) <= (myHalfSize.x + aBoxCollider.myHalfSize.x) &&
		std::abs(myCenter.y - aBoxCollider.myCenter.y) <= (myHalfSize.y + aBoxCollider.myHalfSize.y);
}

bool DragonEngine::BoxCollider::IntersectsSphere(const SphereCollider& aSphereCollider) const
{
	Vector2f min = { myCenter.x - myHalfSize.x, myCenter.y - myHalfSize.y };
	Vector2f max = { myCenter.x + myHalfSize.x, myCenter.y + myHalfSize.y };

	Vector2f closest;
	closest.x = DragonEngine::Max(min.x, DragonEngine::Min(aSphereCollider.GetCenter().x, max.x));
	closest.y = DragonEngine::Max(min.y, DragonEngine::Min(aSphereCollider.GetCenter().y, max.y));

	Vector2f dir = closest - aSphereCollider.GetCenter();

	return dir.LengthSqr() <= aSphereCollider.GetRadius() * aSphereCollider.GetRadius();
}

DragonEngine::Vector2f DragonEngine::BoxCollider::GetCenter() const
{
	return myCenter;
}

void DragonEngine::BoxCollider::SetCenter(const Vector2f& aCenter)
{
	myCenter = aCenter;
}

DragonEngine::Vector2f DragonEngine::BoxCollider::GetHalfSize() const
{
	return myHalfSize;
}

void DragonEngine::BoxCollider::SetHalfSize(const Vector2f& aHalfSize)
{
	myHalfSize = aHalfSize;
}

DragonEngine::ColliderType DragonEngine::BoxCollider::GetType() const
{
	return ColliderType::Box;
}

const char* DragonEngine::BoxCollider::GetTypeName() const
{
	return "BoxCollider";
}

void DragonEngine::BoxCollider::DebugDraw() const
{
	// If the collider is disabled, we don't want to draw it
	if (!IsEnabled())
	{
		return;
	}
	Debug::DrawBox(myCenter - DragonEngine::Vector2f{ myHalfSize.x, myHalfSize.y }, myHalfSize * 2.f, Color::Green);
	Debug::DrawPoint(myCenter, Color::Green);
}