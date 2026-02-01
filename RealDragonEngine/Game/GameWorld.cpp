#include "GameWorld.h"
#include "Sprite.h"

GameWorld::GameWorld() : myDragonEngineLogoSprite(nullptr)
{
}

GameWorld::~GameWorld()
{
}

void GameWorld::Initialize()
{
	myDragonEngineLogoSprite = new DragonEngine::Sprite("Sprites/DragonEngine.png");

	myDragonEngineLogoSprite->SetPosition({ 0.5f, 0.5f });
	myDragonEngineLogoSprite->SetScale({ 0.75f, 0.75f });
	myDragonEngineLogoSprite->SetPivot({ 0.5f, 0.5f });
}

void GameWorld::Update(DragonUtilities::InputManager aInputHandler, float aDeltaTime)
{
	aDeltaTime; aInputHandler; // Unused variable

	// Write update/gameplay logic here
}

void GameWorld::Render()
{
	myDragonEngineLogoSprite->Render();
}
