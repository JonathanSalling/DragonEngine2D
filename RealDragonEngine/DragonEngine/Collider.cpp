#include "BoxCollider.h"
#include "SphereCollider.h"
#include "Collider.h"
#include "Debug.h"

int DragonEngine::Collider::sNextId = 1;

void DragonEngine::Collider::SetEnabled(bool aEnabled)
{
	myEnabled = aEnabled;
}

bool DragonEngine::Collider::IsEnabled() const
{
	return myEnabled;
}

DragonEngine::Collider::Collider() : myId(sNextId++)
{
	myName = "Collider: " + std::to_string(myId);
}

int DragonEngine::Collider::GenerateUniqueId()
{
	myId = sNextId++;
	myName = "Collider: " + std::to_string(myId);
	return myId;
}

void DragonEngine::Collider::SetName(const std::string& aName)
{
	myName = aName;
}

std::string DragonEngine::Collider::GetName() const
{
	return myName;
}
