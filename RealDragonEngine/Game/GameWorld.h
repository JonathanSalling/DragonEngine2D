#pragma once

namespace DragonEngine
{
	class Sprite;
	class Audio;
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

	DragonEngine::Audio* myMusic;
	DragonEngine::Audio* mySoundEffect;
};

