#pragma once

namespace DragonUtilities
{
	class InputManager;
}

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
	void Update(const DragonUtilities::InputManager& aInputHandler, const float& aDeltaTime);
	void Render();

private:
	DragonEngine::Sprite* myDragonEngineLogoSprite;
	float myLogoTime;
};

