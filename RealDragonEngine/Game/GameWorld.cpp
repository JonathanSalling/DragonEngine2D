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
	float aspect = static_cast<float>(DragonEngine::Engine::GetInstance().GetRenderWidth()) /
		static_cast<float>(DragonEngine::Engine::GetInstance().GetRenderHeight());

	// Floaty logo (can and should be removed)
	myLogoTime += aDeltaTime;
	float xOffset = sin(myLogoTime * 2.f) * 0.1f;
	float yOffset = cos(myLogoTime * 2.f) * 0.1f * aspect;
	myDragonEngineLogoSprite->SetPosition({ 0.5f + xOffset, 0.5f + yOffset });
	myDragonEngineLogoSprite->SetRotation(myLogoTime * 45);

	// Fade in and out over time (can and should be removed)
	int minAlpha = 128, maxAlpha = 255;
	float alpha = ((sin(myLogoTime) + 1.f) / 2.f) * (maxAlpha - minAlpha) + minAlpha;
	myDragonEngineLogoSprite->SetColor(DragonEngine::Color::Color(255.f, 255.f, 255.f, alpha));

	// Press space for disable effect (can and should be removed)
	if (aInputHandler.IsKeyDown(DragonUtilities::Key::SPACE))
	{
		myDragonEngineLogoSprite->SetColor(myDragonEngineLogoSprite->GetColor().DisableEffect());
	}

	static DragonEngine::Vector2f oldPos;
	DragonEngine::Debug::DrawLine(oldPos, myDragonEngineLogoSprite->GetPosition(), 1.0f);
	oldPos = myDragonEngineLogoSprite->GetPosition();
	DragonEngine::Debug::DrawPoint({ 0.5f, 0.5f });
	DragonEngine::Debug::DrawCircle({ 0.25f, 0.5f }, static_cast<float>(static_cast<int>(DragonEngine::Timer::GetTotalTime() * 20.0) % DragonEngine::Engine::GetInstance().GetRenderHeight()));
	DragonEngine::Debug::DrawBox({ 0.75f, 0.75f }, { 0.25f, 0.25f });

	// Write update/gameplay logic here
}

void GameWorld::Render()
{
	myDragonEngineLogoSprite->Render();

	DragonEngine::Debug::Render(DragonEngine::Engine::GetInstance().GetRenderer());
}
