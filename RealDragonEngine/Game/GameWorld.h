#pragma once
#include "BoxCollider.h"
#include "SphereCollider.h"

#include <vector>

namespace DragonEngine
{
	class Sprite;
	class InputManager;
}

class GameWorld
{
public:
	GameWorld();
	~GameWorld();
	void Initialize();
	void Update(const DragonEngine::InputManager& aInputHandler, const float& aDeltaTime);
	void Render();

private:
	DragonEngine::BoxCollider myPlayerCollider;
	std::vector<DragonEngine::BoxCollider> myEnemyColliders;
	std::vector<DragonEngine::SphereCollider> myBulletColliders;

	DragonEngine::Sprite* myDragonEngineLogoSprite;
	float myLogoTime = 0.f;
};

