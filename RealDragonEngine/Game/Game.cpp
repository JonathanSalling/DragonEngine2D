#include "Game.h"
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

int Game::Init()
{
	if (DragonEngine::Engine::GetInstance().Start() == 2)
	{
		return 2;
	}

	/* Initialization code can go here. */
	myGameWorld.Initialize();

	return 0;  /* carry on with the program! */
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
	DragonEngine::Engine::GetInstance().StartRender();

	/* ask the game world to render itself. */
	myGameWorld.Render();

	DragonEngine::Engine::GetInstance().RenderPresent();
}

bool Game::UpdateInput()
{
	if (myInputManager->Update())
	{
		return true;
	}

	return false;
}


