#pragma once
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
	DragonEngine::Sprite* myDragonEngineLogoSprite;
};

