#pragma once
#include "GameWorld.h"

namespace DragonEngine
{
	class InputManager;
	class Timer;
	class PerformanceTracker;
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
	DragonEngine::InputManager* myInputManager;
	DragonEngine::PerformanceTracker* myPerformanceTracker;
};

