#include "GameWorld.h"
#include "Sprite.h"
#include <InputManager.h>
#include <Engine.h>
#include <Debug.h>
#include "Timer.hpp"

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

	myDragonEngineLogoSprite->SetPosition({ 0.5f, 0.5f });
	myDragonEngineLogoSprite->SetScale({ 0.75f, 0.75f });
	myDragonEngineLogoSprite->SetPivot({ 0.5f, 0.5f });
}

void GameWorld::Update(const DragonUtilities::InputManager& aInputHandler, const float& aDeltaTime)
{
	aInputHandler;

	// Example update logic for the logo sprite (should be removed)
	{
		float aspect = static_cast<float>(DragonEngine::Engine::GetInstance().GetRenderWidth()) /
			static_cast<float>(DragonEngine::Engine::GetInstance().GetRenderHeight());

		// Floaty logo (should be removed)
		myLogoTime += aDeltaTime;
		float xOffset = sin(myLogoTime * 2.f) * 0.1f;
		float yOffset = cos(myLogoTime * 2.f) * 0.1f * aspect;
		myDragonEngineLogoSprite->SetPosition({ 0.5f + xOffset, 0.5f + yOffset });
		myDragonEngineLogoSprite->SetRotation(myLogoTime * 45);

		// Change color over time (should be removed)
		if ((int)myLogoTime % 2 == 0)
		{
			myDragonEngineLogoSprite->SetColor(DragonEngine::Color::Red);
		}
		else if ((int)myLogoTime % 3 == 0)
		{
			myDragonEngineLogoSprite->SetColor(DragonEngine::Color::Green);
		}
		else
		{
			myDragonEngineLogoSprite->SetColor(DragonEngine::Color::White);
		}

		// Fade in and out over time (should be removed)
		DragonEngine::Color currentColor = myDragonEngineLogoSprite->GetColor();
		int minAlpha = 64, maxAlpha = 255;
		float alpha = ((sin(myLogoTime) + 1.f) / 2.f) * (maxAlpha - minAlpha) + minAlpha;
		myDragonEngineLogoSprite->SetColor(DragonEngine::Color::Color(currentColor.r, currentColor.g, currentColor.b, alpha));

		// Draw debug shapes (should be removed)
		static DragonEngine::Vector2f oldPos;
		DragonEngine::Debug::DrawLine(oldPos, myDragonEngineLogoSprite->GetPosition(), 1.0f);
		oldPos = myDragonEngineLogoSprite->GetPosition();
		DragonEngine::Debug::DrawPoint({ 0.5f, 0.5f });
		DragonEngine::Debug::DrawCircle({ 0.25f, 0.5f }, std::fmodf(static_cast<float>(DragonEngine::Timer::GetTotalTime() * 0.2f), 0.5f));
		DragonEngine::Debug::DrawBox({ 0.75f, 0.75f }, { 0.25f, 0.25f });

		// Write update/gameplay logic here
	}
}

void GameWorld::Render()
{
	myDragonEngineLogoSprite->Render();

	DragonEngine::Debug::Render(DragonEngine::Engine::GetInstance().GetRenderer());
}
