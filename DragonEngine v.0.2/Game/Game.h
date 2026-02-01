#pragma once
#include "GameWorld.h"
#include <Timer.h>
#include <InputManager.h>
#include "Engine.h"

class Game
{
public:
	Game();
	~Game();
	SDL_AppResult Init();
	void ShutdownGame();
	void InitCallBack();
	void UpdateCallBack();
	void RenderCallBack();

	// The engine forwards raw SDL events to the game layer.
	bool UpdateInput(const SDL_Event& anEvent);

private:
	GameWorld myGameWorld;
	DragonUtilities::InputManager myInputManager;
	DragonUtilities::Timer myTimer;
};

