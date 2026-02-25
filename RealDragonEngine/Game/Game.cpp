#include "Game.h"
#include <SDL3/SDL_render.h>
#include "InputManager.h"
#include "Timer.h"
#include <Engine.h>

Game::Game()
{
	myInputManager = new DragonUtilities::InputManager();
	myTimer = new DragonUtilities::Timer();
}

Game::~Game()
{
	delete myInputManager;
	myInputManager = nullptr;

	delete myTimer;
	myTimer = nullptr;
}

SDL_AppResult Game::Init()
{
	if (DragonEngine::Engine::GetInstance().Start() == SDL_APP_FAILURE)
	{
		return SDL_APP_FAILURE;
	}

	/* Initialization code can go here. */
	myGameWorld.Initialize();

	return SDL_APP_CONTINUE;  /* carry on with the program! */
}

void Game::ShutdownGame()
{
	DragonEngine::Engine::GetInstance().Shutdown();
}

void Game::InitCallBack()
{
	myGameWorld.Initialize();
}

void Game::UpdateCallBack()
{
	myTimer->Update();
	myGameWorld.Update(*myInputManager, myTimer->GetDeltaTime());
	RenderCallBack();
}

void Game::RenderCallBack()
{
	/* choose the color for the frame we will draw.*/
	const float red = 124.f / 255.f;
	const float green = 196.f / 255.f;
	const float blue = 0.f / 255.f;
	SDL_SetRenderDrawColorFloat(DragonEngine::Engine::GetInstance().GetRenderer(), red, green, blue, SDL_ALPHA_OPAQUE_FLOAT);  /* new color, full alpha. */

	/* clear the window to the draw color. */
	SDL_RenderClear(DragonEngine::Engine::GetInstance().GetRenderer());

	/* ask the game world to render itself. */
	myGameWorld.Render();

	/* put the newly-cleared rendering on the screen. */
	SDL_RenderPresent(DragonEngine::Engine::GetInstance().GetRenderer());
}

bool Game::UpdateInput(const SDL_Event& anEvent)
{
	if (myInputManager->UpdateEvents(anEvent))
	{
		return true;
	}

	return false;
}


