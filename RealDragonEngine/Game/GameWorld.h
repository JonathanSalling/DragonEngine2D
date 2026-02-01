#pragma once

#include "InputManager.h"
#include "Timer.h"

namespace DragonEngine
{
	class Sprite;
}

class GameWorld
{
public:
	GameWorld();
	~GameWorld();
	void Initialize();
	void Update(DragonUtilities::InputManager aInputHandler, float aDeltaTime);
	void Render();

private:
	DragonEngine::Sprite* myDragonEngineLogoSprite;
};

