#include "GameWorld.h"
#include "Sprite.h"
#include <InputManager.h>
#include <Engine.h>

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
	// Example input handling (can and should be removed)

	float aspect = static_cast<float>(DragonEngine::Engine::GetInstance().GetRenderWidth()) /
		static_cast<float>(DragonEngine::Engine::GetInstance().GetRenderHeight());

	// Floaty logo (can and should be removed)
	myLogoTime += aDeltaTime;
	float xOffset = sin(myLogoTime * 2.f) * 0.1f;
	float yOffset = cos(myLogoTime * 2.f) * 0.1f * aspect;
	myDragonEngineLogoSprite->SetPosition({ 0.5f + xOffset, 0.5f + yOffset });

	// Fade in and out over time (can and should be removed)
	int minAlpha = 128, maxAlpha = 255;
	float alpha = ((sin(myLogoTime) + 1.f) / 2.f) * (maxAlpha - minAlpha) + minAlpha;
	myDragonEngineLogoSprite->SetColor(DragonEngine::Color::Color(255.f, 255.f, 255.f, alpha));

	if (aInputHandler.IsKeyDown(DragonUtilities::Key::SPACE))
	{
		myDragonEngineLogoSprite->SetColor(myDragonEngineLogoSprite->GetColor().Grayscale());
	}

	// Write update/gameplay logic here
}

void GameWorld::Render()
{
	myDragonEngineLogoSprite->Render();
}
