#include "Game.h"
#include <Engine.h>
#include "InputManager.h"
#include "PerformanceTracker.h"
#include "Timer.hpp"

Game::Game()
{
	myInputManager = new DragonEngine::InputManager();
	myPerformanceTracker = new DragonEngine::PerformanceTracker();
}

Game::~Game()
{
	delete myInputManager;
	delete myPerformanceTracker;
	myInputManager = nullptr;
	myPerformanceTracker = nullptr;
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
	myPerformanceTracker->Update();
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


