#pragma once
#include "GameWorld.h"

namespace DragonUtilities
{
	class InputManager;
	class Timer;
}

union SDL_Event;

class Game
{
public:
	Game();
	~Game();
	int Init();
	void ShutdownGame();
	void InitCallBack();
	void UpdateCallBack();
	void RenderCallBack();

	bool UpdateInput();

private:
	GameWorld myGameWorld;
	DragonUtilities::InputManager* myInputManager;
};

