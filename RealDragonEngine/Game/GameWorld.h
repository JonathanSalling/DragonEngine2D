#pragma once

#include "Player.h"
#include "InputManager.h"
#include "Timer.h"

#include "TemplateUtilities.h"

class GameWorld
{
public:
	GameWorld();
	~GameWorld();
	void Initialize();
	void Update(DragonUtilities::InputManager aInputHandler, float aDeltaTime);
	void Render();

private:
	SDL_Texture* DragonEngineIconTexture;
	Player myPlayer;
};

