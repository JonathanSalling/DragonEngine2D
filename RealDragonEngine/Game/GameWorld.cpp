#include "Text.h"
#include "GameWorld.h"
#include "Sprite.h"
#include <InputManager.h>
#include <Engine.h>
#include <Debug.h>
#include "Timer.hpp"
#include <iostream>
#include "Color.h"
#include "Audio.h"

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

	myMusic = new DragonEngine::Audio("Sounds/music.mp3");
	mySoundEffect = new DragonEngine::Audio("Sounds/anime.mp3");

	myMusic->Play(true);
	mySoundEffect->PlayOneshot();
}

void GameWorld::Update(const DragonEngine::InputManager& aInputHandler, const float& aDeltaTime)
{
	// Write update/gameplay logic here
	aInputHandler, aDeltaTime;

	myDragonEngineLogoSprite->Update(aDeltaTime);
}

void GameWorld::Render()
{
	// Write rendering logic here

	myDragonEngineLogoSprite->Render();

	// Example Text
	DragonEngine::Text temp = DragonEngine::Text("Hello World!", 100, "Fonts/wingding.ttf");
	temp.SetPosition({ 0.5f,0.5f });
	temp.SetPivot({ 0.5f,0.5f });
	temp.Render();

	DragonEngine::Debug::Render(DragonEngine::Engine::GetInstance().GetRenderer());
}
