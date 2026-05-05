#pragma once
#include <vector>
#include <SphereCollider.h>
#include "BoxCollider.h"

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
	DragonEngine::Sprite* myDragonEngineLogoSprite;

	DragonEngine::BoxCollider tempCollider;
	DragonEngine::BoxCollider tempCollider2;	
	DragonEngine::SphereCollider tempCollider3;
	DragonEngine::SphereCollider tempCollider4;
};

