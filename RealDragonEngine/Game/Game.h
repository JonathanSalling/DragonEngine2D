#pragma once
#include "GameWorld.h"
//#include "Engine.h"

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

	// The engine forwards raw SDL events to the game layer.
	bool UpdateInput();

private:
	GameWorld myGameWorld;
	DragonUtilities::InputManager* myInputManager;
	DragonUtilities::Timer* myTimer;
};

