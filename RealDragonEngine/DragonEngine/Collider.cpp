#include "Collider.h"

DragonEngine::Collider::Collider() : myId(GenerateUniqueId())
{
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
