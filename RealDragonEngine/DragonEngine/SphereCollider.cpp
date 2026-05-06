#include "BoxCollider.h"
#include "Debug.h"
#include "SphereCollider.h"
#include "Engine.h"

DragonEngine::SphereCollider::SphereCollider() : myCenter{ 0,0 }, myRadius(0), Collider() // Call base class default constructor to initialize enabled state and name
{
}

DragonEngine::SphereCollider::SphereCollider(const SphereCollider& aSphere)
	: myCenter(aSphere.myCenter), myRadius(aSphere.myRadius), Collider(aSphere) // Call base class copy constructor to copy enabled state and name
{
}

DragonEngine::SphereCollider::SphereCollider(const Vector2f& aCenter, float aRadius)
	: myCenter(aCenter), myRadius(aRadius), Collider() // Call base class default constructor to initialize enabled state and name
{
}

bool DragonEngine::SphereCollider::IsInside(const Vector2f& aPosition) const
{
	// If the collider is disabled, we consider no position to be inside it
	if (!IsEnabled())
	{
		return false;
	}

	Vector2f distance = aPosition - myCenter;
	return distance.LengthSqr() <= (myRadius * myRadius);
}

float DragonEngine::SphereCollider::GetRadius() const
{
	return myRadius;
}

void DragonEngine::SphereCollider::SetRadius(float aRadius)
{
	myRadius = aRadius;
}

DragonEngine::ColliderType DragonEngine::SphereCollider::GetType() const
{
	return ColliderType::Sphere;
}

const char* DragonEngine::SphereCollider::GetTypeName() const
{
	return "SphereCollider";
}

bool DragonEngine::SphereCollider::Intersects(const Collider& other) const
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

bool DragonEngine::SphereCollider::IntersectsBox(const BoxCollider& other) const
{
	return other.Intersects(*this);
}

bool DragonEngine::SphereCollider::IntersectsSphere(const SphereCollider& other) const
{
	DragonEngine::Vector2f screenCenter = Engine::GetInstance().NormalSpaceToScreenSpace(myCenter);
	DragonEngine::Vector2f otherScreenCenter = Engine::GetInstance().NormalSpaceToScreenSpace(other.GetCenter());

	DragonEngine::Vector2f distance = otherScreenCenter - screenCenter;

	float screenRadius = myRadius * Engine::GetInstance().GetRenderHeight();
	float otherScreenRadius = other.GetRadius() * Engine::GetInstance().GetRenderHeight();

	float r = screenRadius + otherScreenRadius;

	return distance.LengthSqr() <= r * r;
}

DragonEngine::Vector2f DragonEngine::SphereCollider::GetCenter() const
{
	return myCenter;
}

void DragonEngine::SphereCollider::SetCenter(const Vector2f& aCenter)
{
	myCenter = aCenter;
}

void DragonEngine::SphereCollider::DebugDraw() const
{
	// If the collider is disabled, we don't want to draw it
	if (!IsEnabled())
	{
		return;
	}
	Debug::DrawCircle(myCenter, myRadius, Color::Green);
	Debug::DrawPoint(myCenter, Color::Green);
}