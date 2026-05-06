#include "BoxCollider.h"
#include "Debug.h"
#include "SphereCollider.h"
#include "TemplateUtilities.h"
#include "Engine.h"

DragonEngine::BoxCollider::BoxCollider() : myCenter{ 0, 0 }, myHalfSize{ 0.f, 0.f }, Collider() // Call base class default constructor to initialize enabled state and name
{
}

DragonEngine::BoxCollider::BoxCollider(const BoxCollider& aBoxCollider)
	: myCenter(aBoxCollider.myCenter), myHalfSize(aBoxCollider.myHalfSize), Collider(aBoxCollider) // Call base class copy constructor to copy enabled state and name
{
}

DragonEngine::BoxCollider::BoxCollider(const Vector2f& aCenter, const Vector2f& aHalfSize)
	: myCenter(aCenter), myHalfSize(aHalfSize), Collider() // Call base class default constructor to initialize enabled state and name
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
	Vector2f screenCenter = Engine::GetInstance().NormalSpaceToScreenSpace(myCenter);
	Vector2f otherScreenCenter = Engine::GetInstance().NormalSpaceToScreenSpace(aBoxCollider.myCenter);

	Vector2f screenSize = {
		myHalfSize.x * Engine::GetInstance().GetRenderWidth(),
		myHalfSize.y * Engine::GetInstance().GetRenderHeight()
	};

	Vector2f otherScreenSize = {
		aBoxCollider.myHalfSize.x * Engine::GetInstance().GetRenderWidth(),
		aBoxCollider.myHalfSize.y * Engine::GetInstance().GetRenderHeight()
	};

	return std::abs(screenCenter.x - otherScreenCenter.x) <= (screenSize.x + otherScreenSize.x) &&
		std::abs(screenCenter.y - otherScreenCenter.y) <= (screenSize.y + otherScreenSize.y);
}

bool DragonEngine::BoxCollider::IntersectsSphere(const SphereCollider& aSphereCollider) const
{
	Vector2f screenCenter = Engine::GetInstance().NormalSpaceToScreenSpace(myCenter);
	Vector2f otherSphereCenter = Engine::GetInstance().NormalSpaceToScreenSpace(aSphereCollider.GetCenter());

	Vector2f screenHalfSize = {
		myHalfSize.x * Engine::GetInstance().GetRenderWidth(),
		myHalfSize.y * Engine::GetInstance().GetRenderHeight()
	};

	float radius = aSphereCollider.GetRadius() * Engine::GetInstance().GetRenderHeight();

	Vector2f min = screenCenter - screenHalfSize;
	Vector2f max = screenCenter + screenHalfSize;

	Vector2f closest;
	closest.x = std::max(min.x, std::min(otherSphereCenter.x, max.x));
	closest.y = std::max(min.y, std::min(otherSphereCenter.y, max.y));

	Vector2f dir = otherSphereCenter - closest;

	return dir.LengthSqr() <= radius * radius;
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