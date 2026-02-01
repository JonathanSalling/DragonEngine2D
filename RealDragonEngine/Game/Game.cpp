#include "Game.h"
#include <Engine.h>

Game::Game()
{

}

Game::~Game()
{

}

SDL_AppResult Game::Init()
{
	if (Engine::GetInstance().Start() == SDL_APP_FAILURE)
	{
		system("pause");
		return SDL_APP_FAILURE;
	}

	/* Initialization code can go here. */
	myGameWorld.Initialize();

	return SDL_APP_CONTINUE;  /* carry on with the program! */
}

void Game::ShutdownGame()
{
	Engine::GetInstance().Shutdown();
}

void Game::InitCallBack()
{
	myGameWorld.Initialize();
}

void Game::UpdateCallBack()
{
	myTimer.Update();
	myGameWorld.Update(myInputManager, myTimer.GetDeltaTime());

	/* choose the color for the frame we will draw.*/
	const float red = 124.f / 255.f;
	const float green = 196.f / 255.f;
	const float blue = 0.f / 255.f;
	SDL_SetRenderDrawColorFloat(Engine::GetInstance().myRenderer, red, green, blue, SDL_ALPHA_OPAQUE_FLOAT);  /* new color, full alpha. */

	/* clear the window to the draw color. */
	SDL_RenderClear(Engine::GetInstance().myRenderer);

	/* ask the game world to render itself. */
	myGameWorld.Render();

	/* put the newly-cleared rendering on the screen. */
	SDL_RenderPresent(Engine::GetInstance().myRenderer);

}

bool Game::UpdateInput(const SDL_Event& anEvent)
{
	if (myInputManager.UpdateEvents(anEvent))
	{
		return true;
	}

	return false;
}


