#include "GameWorld.h"
#include "Sprite.h"
#include <InputManager.h>

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
	//myLogoTime += aDeltaTime;
	//float xOffset = sin(myLogoTime * 2.f) * 0.1f;
	//float yOffset = sin((myLogoTime + 10) * 2.f) * 0.01f;
	//myDragonEngineLogoSprite->SetPosition({ 0.5f + xOffset, 0.5f + yOffset });


	const DragonEngine::Vector2<float> currentPosition = myDragonEngineLogoSprite->GetPosition();
	if (aInputHandler.IsKeyDown(DragonUtilities::Key::A))
	{
		myDragonEngineLogoSprite->SetPosition({ currentPosition.x - 0.5f * aDeltaTime, currentPosition.y });
	}

	if (aInputHandler.IsKeyPressed(DragonUtilities::Key::D))
	{
		myDragonEngineLogoSprite->SetPosition({ currentPosition.x + 0.5f , currentPosition.y });
	}

	if (aInputHandler.IsMousePressed(DragonUtilities::MouseButton::LEFT))
	{
		myDragonEngineLogoSprite->SetPosition({ currentPosition.x + 0.5f , currentPosition.y });
	}

	// Write update/gameplay logic here
}

void GameWorld::Render()
{
	myDragonEngineLogoSprite->Render();
}
