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
	void Update(DragonUtilities::InputManager aInputHandler, float aDeltaTime);
	void Render();

private:
	DragonEngine::Sprite* myDragonEngineLogoSprite;
	float myLogoTime;
};

