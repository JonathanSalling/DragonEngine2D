#include "Text.h"
#include "GameWorld.h"
#include "Sprite.h"
#include <InputManager.h>
#include <Engine.h>
#include <Debug.h>
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
	myDragonEngineLogoSprite->SetPosition({ 0.5f, 0.5f });
	myDragonEngineLogoSprite->SetScale({ 0.75f, 0.75f });
	myDragonEngineLogoSprite->SetPivot({ 0.5f, 0.5f });

	// Example of using sprite sheet animation functions
	int rows = 2;
	int columns = 2;
	int frameCount = 4;
	myDragonEngineLogoSprite->SetSpriteSheet(rows, columns, frameCount);
	myDragonEngineLogoSprite->SetAnimationFPS(1);
	myDragonEngineLogoSprite->SetLooping(false);
	//myDragonEngineLogoSprite->Stop();
	//myDragonEngineLogoSprite->SetFrame(3);
	//myDragonEngineLogoSprite->Play();
	//myDragonEngineLogoSprite->Pause();
	//myDragonEngineLogoSprite->ClearSpriteSheet();

	// Example of using the Audio class to play music and sound effects
	myMusic = new DragonEngine::Audio("Sounds/music.mp3");
	mySoundEffect = new DragonEngine::Audio("Sounds/anime.mp3");

	myMusic->Play(true); // Set music to loop indefinitely and play it
	myMusic->SetLoops(-1);
	myMusic->SetVolume(2.5f); // Set music volume to 50%
	myMusic->Stop(5); // Stop music with a 5-second fade-out

	mySoundEffect->PlayOneshot(); // Play the sound effect once without affecting the music track
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

	DragonEngine::Text tempText = DragonEngine::Text("Text rendering works!", 100, "Fonts/arial.ttf");
	tempText.SetPosition({ 0.5f,0.25f });
	tempText.SetPivot({ 0.5f,0.5f });
	tempText.Render();

	// Example of rendering text
	DragonEngine::Text tempText2 = DragonEngine::Text("Text rendering works!", 100, "Fonts/wingding.ttf");
	tempText2.SetPosition({ 0.5f,0.5f });
	tempText2.SetPivot({ 0.5f,0.5f });
	tempText2.SetText("Hello World!");
	tempText2.Render();


	DragonEngine::Debug::Render(DragonEngine::Engine::GetInstance().GetRenderer());
}
