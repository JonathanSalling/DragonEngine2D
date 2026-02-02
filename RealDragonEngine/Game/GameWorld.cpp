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
	aInputHandler; // Unused variable
	myLogoTime += aDeltaTime;
	float xOffset = sin(myLogoTime * 2.f) * 0.1f;
	float yOffset = sin((myLogoTime + 10) * 2.f) * 0.01f;
	myDragonEngineLogoSprite->SetPosition({ 0.5f + xOffset, 0.5f + yOffset });

	// Write update/gameplay logic here
}

void GameWorld::Render()
{
	myDragonEngineLogoSprite->Render();
}
