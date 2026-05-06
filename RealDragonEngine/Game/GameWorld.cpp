#include "Text.h"
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

	//myDragonEngineLogoSprite->SetSpriteSheet(2, 2, 4);

	myDragonEngineLogoSprite->SetPosition({ 0.5f, 0.5f });
	myDragonEngineLogoSprite->SetScale({ 0.75f, 0.75f });
	myDragonEngineLogoSprite->SetPivot({ 0.5f, 0.5f });

	tempCollider.SetCenter({ 0.5f, 0.5f });
	tempCollider.SetHalfSize({ 0.1f, 0.1f });
	tempCollider2.SetCenter({ 0.75f, 0.5f });
	tempCollider2.SetHalfSize({ 0.1f, 0.1f });
	tempCollider3.SetCenter({ 0.75f, 0.25f });
	tempCollider3.SetRadius(0.1f);

	tempCollider4.SetCenter({ 0.5f, 0.25f });
	tempCollider4.SetRadius(0.1f);
}

void GameWorld::Update(const DragonEngine::InputManager& aInputHandler, const float& aDeltaTime)
{
	// Write update/gameplay logic here
	aInputHandler, aDeltaTime;

	myDragonEngineLogoSprite->Update(aDeltaTime);

	tempCollider.SetCenter(tempCollider.GetCenter() + DragonEngine::Vector2f{ 0.01f,0 } * aDeltaTime);
	tempCollider3.SetCenter(tempCollider3.GetCenter() + DragonEngine::Vector2f{ 0,0.01f } * aDeltaTime);
	tempCollider4.SetCenter(tempCollider4.GetCenter() + DragonEngine::Vector2f{ 0.01f,0.01f } * aDeltaTime);

	tempCollider.DebugDraw();
	tempCollider2.DebugDraw();
	tempCollider3.DebugDraw();
	tempCollider4.DebugDraw();

	if (tempCollider.Intersects(tempCollider2) )
	{
		std::cout << "Colliders 1 and 2 intersecting!" << std::endl;
	}

	if (tempCollider3.Intersects(tempCollider2))
	{
		std::cout << "Colliders 2 and 3 intersecting!" << std::endl;
	}

	if (tempCollider4.Intersects(tempCollider2))
	{
		std::cout << "Colliders 2 and 4 intersecting!" << std::endl;
	}



	// Draw debug shapes (should be removed)
	DragonEngine::Debug::DrawCircle({ 0.25f, 0.5f }, 0.1f, DragonEngine::Color::Blue);
}

void GameWorld::Render()
{
	// Write rendering logic here

	myDragonEngineLogoSprite->Render();

	DragonEngine::Text temp = DragonEngine::Text("Hello World!", 100);
	temp.SetPosition({ 0.5f,0.5f });
	temp.SetPivot({ 0.5f,0.5f });
	temp.Render();

	DragonEngine::Debug::Render(DragonEngine::Engine::GetInstance().GetRenderer());
}
