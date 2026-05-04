#include "GameWorld.h"
#include "Sprite.h"
#include <InputManager.h>
#include <Engine.h>
#include <Debug.h>
#include "Timer.hpp"
#include <iostream>
#include "Color.h"

GameWorld::GameWorld() : myDragonEngineLogoSprite(nullptr)
{
}

GameWorld::~GameWorld()
{
	delete myDragonEngineLogoSprite;
	myDragonEngineLogoSprite = nullptr;
}

void GameWorld::Initialize()
{
	myDragonEngineLogoSprite = new DragonEngine::Sprite("Sprites/DragonEngine.png");

	myDragonEngineLogoSprite->SetSpriteSheet(2, 2, 4);

	myDragonEngineLogoSprite->SetPosition({ 0.5f, 0.5f });
	myDragonEngineLogoSprite->SetScale({ 0.75f, 0.75f });
	myDragonEngineLogoSprite->SetPivot({ 0.5f, 0.5f });
}

void GameWorld::Update(const DragonEngine::InputManager& aInputHandler, const float& aDeltaTime)
{
	// Write update/gameplay logic here
	aInputHandler, aDeltaTime;

	myDragonEngineLogoSprite->Update(aDeltaTime);

	// Draw debug shapes (should be removed)
	DragonEngine::Debug::DrawCircle({ 0.25f, 0.5f }, 0.1f, DragonEngine::Color::Blue);
}

void GameWorld::Render()
{
	// Write rendering logic here

	myDragonEngineLogoSprite->Render();

	DragonEngine::Debug::Render(DragonEngine::Engine::GetInstance().GetRenderer());
}
