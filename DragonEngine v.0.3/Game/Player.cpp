#include "Player.h"
#include <InputManager.h>

Player::Player() :
	myTexture(nullptr), myPosition(0.f, 0.f),
	myVelocity(0.f, 0.f), mySpeed(0.f)
{

}

Player::~Player()
{
	myTexture = nullptr;
}

void Player::Initialize()
{
	myTexture = new DragonEngine::Sprite("Sprites/DragonEngine.png");
	myPosition = DragonUtilities::Vector2<float>(0.5f, 0.5f);
	mySpeed = 1.0f; // pixels per second
	myTexture->SetScale({ 0.5f, 0.5f });
	myTexture->SetPivot({ 0.5f, 0.5f });
}

void Player::Update(float aDeltaTime, const DragonUtilities::InputManager& aInputManager)
{
	myVelocity = DragonUtilities::Vector2<float>(0, 0);

	if (aInputManager.IsKeyDown(SDL_SCANCODE_LEFT))
	{
		myVelocity = DragonUtilities::Vector2<float>(-1.f, 0);
	}
	if (aInputManager.IsKeyDown(SDL_SCANCODE_RIGHT))
	{
		myVelocity = DragonUtilities::Vector2<float>(1.f, 0);
	}
	if (aInputManager.IsKeyDown(SDL_SCANCODE_UP))
	{
		myVelocity = DragonUtilities::Vector2<float>(0, -1.f);
	}
	if (aInputManager.IsKeyDown(SDL_SCANCODE_DOWN))
	{
		myVelocity = DragonUtilities::Vector2<float>(0, 1.f);
	}

	myPosition += myVelocity * aDeltaTime * mySpeed;
}

void Player::SetPosition(const DragonUtilities::Vector2<float>& aPosition)
{
	myPosition = aPosition;
}

void Player::SetVelocity(const DragonUtilities::Vector2<float>& aVelocity)
{
	myVelocity = aVelocity;
}

const DragonUtilities::Vector2<float>& Player::GetPosition() const
{
	return myPosition;
}

const DragonUtilities::Vector2<float>& Player::GetVelocity() const
{
	return myVelocity;
}

float Player::GetWidth() const
{
	return myTexture->GetScale().x;
}

float Player::GetHeight() const
{
	return myTexture->GetScale().y;
}

void Player::Render()
{
	SDL_FRect playerRect = { myPosition.x, myPosition.y, (float)GetWidth() * 0.5f, (float)GetHeight() * 0.5f };

	// Center the rectangle around the position
	playerRect.x = myPosition.x - playerRect.w * 0.5f;
	playerRect.y = myPosition.y - playerRect.h * 0.5f;

	myTexture->SetPosition({ myPosition.x,myPosition.y });

	myTexture->Render();
}
