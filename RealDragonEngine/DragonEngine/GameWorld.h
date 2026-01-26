#pragma once

#include "Player.h"
#include "DragonUtilities/InputManager.h"
#include <DragonUtilities/Timer.h>

class GameWorld
{
public:
	GameWorld();
	~GameWorld();
	void Initialize();
	void Update(float deltaTime);

	DragonUtilities::Timer& GetTimer() { return myTimer; }
	DragonUtilities::InputManager& GetInputManager() { return myInputManager; }

private:
	//Player myPlayer;
	DragonUtilities::InputManager myInputManager;
	DragonUtilities::Timer myTimer;
};

