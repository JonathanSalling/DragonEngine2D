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

	myDragonEngineLogoSprite->SetSpriteSheet(2, 2);

	myDragonEngineLogoSprite->SetPosition({ 0.5f, 0.5f });
	myDragonEngineLogoSprite->SetScale({ 0.75f, 0.75f });
	myDragonEngineLogoSprite->SetPivot({ 0.5f, 0.5f });


	// This is just example data to demonstrate the API, not actual gameplay logic
	myPlayerCollider.SetCenter({ 0.5f, 0.4f });
	myPlayerCollider.SetHalfSize({ 0.05f, 0.05f });

	float posX = 0.1f;
	for (size_t i = 0; i < 5; i++)
	{
		myBulletColliders.emplace_back(DragonEngine::Vector2f{ posX, 0.8f }, 0.01f);
		myEnemyColliders.emplace_back(DragonEngine::Vector2f{ posX, 0.1f }, DragonEngine::Vector2f{ 0.01f, 0.02f });
		posX += 0.2f;
	}
}

void GameWorld::Update(const DragonEngine::InputManager& aInputHandler, const float& aDeltaTime)
{
	// Write update/gameplay logic here
	aInputHandler, aDeltaTime;

	myDragonEngineLogoSprite->Update(aDeltaTime);

	// This is example logic to demonstrate how to use the colliders and debug drawing; replace with actual gameplay logic as needed.

	// Update colliders' positions (example movement logic)

	// Example: move bullets upwards
	for (DragonEngine::SphereCollider& bullet : myBulletColliders)
	{
		DragonEngine::Vector2f pos = bullet.GetCenter();
		pos.y -= 0.05f * aDeltaTime;
		bullet.SetCenter(pos);
	}

	// Example: move enemies downwards
	for (DragonEngine::BoxCollider& enemy : myEnemyColliders)
	{
		DragonEngine::Vector2f pos = enemy.GetCenter();
		pos.y += 0.05f * aDeltaTime;
		enemy.SetCenter(pos);
	}

	// Collision check: bullets vs enemies

	for (size_t i = 0; i < myBulletColliders.size(); i++)
	{
		for (size_t j = 0; j < myEnemyColliders.size(); j++)
		{
			if (myBulletColliders[i].Intersects(myEnemyColliders[j]))
			{
				// Example gameplay response
				myBulletColliders[i].SetEnabled(false);
				myEnemyColliders[j].SetEnabled(false);

				// Debug feedback
				DragonEngine::Debug::DrawPoint(
					myEnemyColliders[j].GetCenter(), DragonEngine::Color::Red,
					1.0f
				);
			}
		}
	}

	// Collision check: player vs enemies

	for (DragonEngine::Collider& enemy : myEnemyColliders)
	{
		if (myPlayerCollider.Intersects(enemy))
		{
			if (enemy.IsEnabled())
			{
				// Player hit
				std::cout << "Player hit!\n";

				enemy.SetEnabled(false);
			}
		}
	}

	// Cleanup: remove disabled colliders example
	// Simple but inefficient way to remove disabled colliders 
	for (size_t i = 0; i < myBulletColliders.size(); i++)
	{
		if (myBulletColliders[i].IsEnabled() == false)
		{
			myBulletColliders.erase(myBulletColliders.begin() + i);
			i--;
		}
	}

	// Draw debug shapes (should be removed)
	DragonEngine::Debug::DrawCircle({ 0.25f, 0.5f }, 0.1f, DragonEngine::Color::Blue);
}

void GameWorld::Render()
{
	// Write rendering logic here

	// This is just example rendering code to demonstrate the API, not actual gameplay rendering logic
	for (DragonEngine::SphereCollider& bullet : myBulletColliders)
	{
		bullet.DebugDraw();
	}
	for (DragonEngine::BoxCollider& enemy : myEnemyColliders)
	{
		enemy.DebugDraw();
	}
	myPlayerCollider.DebugDraw();

	myDragonEngineLogoSprite->Render();

	DragonEngine::Debug::Render(DragonEngine::Engine::GetInstance().GetRenderer());
}
