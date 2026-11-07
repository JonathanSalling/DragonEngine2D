#include "Game.h"
#include "InputManager.h"
#include "Timer.hpp"
#include <Engine.h>

Game::Game()
{
	myInputManager = new DragonEngine::InputManager();
}

Game::~Game()
{
	delete myInputManager;
	myInputManager = nullptr;
}

int Game::Init()
{
	if (DragonEngine::Engine::GetInstance().Start() == 2)
	{
		return 2;
	}

	/* Initialization code can go here. */
	InitCallBack();

	return 0;  /* carry on with the program! */
}

void Game::ShutdownGame()
{
	DragonEngine::Engine::GetInstance().Shutdown();
	std::exit(0);
}

void Game::InitCallBack()
{
	myGameWorld.Initialize();
}

void Game::UpdateCallBack()
{
	DragonEngine::Timer::Update();
	myGameWorld.Update(*myInputManager, DragonEngine::Timer::GetDeltaTime());
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


