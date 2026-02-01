#include "GameWorld.h"
#include <Engine.h>

GameWorld::GameWorld()
{
}

GameWorld::~GameWorld()
{
}

void GameWorld::Initialize()
{
	/* Load a image */
	DragonEngineIconTexture = IMG_LoadTexture(Engine::GetInstance().myRenderer, "DragonEngine.png");
	if (!DragonEngineIconTexture)
	{
		SDL_Log("Couldn't load icon: %s\n", SDL_GetError());
	}

	myPlayer.Initialize(*DragonEngineIconTexture);
}

void GameWorld::Update(DragonUtilities::InputManager aInputHandler, float aDeltaTime)
{
	myPlayer.Update(aDeltaTime, aInputHandler);
}

void GameWorld::Render()
{
	myPlayer.Render(*Engine::GetInstance().myRenderer);
}
