#include "Player.h"

Player::Player()
{
	myPosition = DragonUtilities::Vector2<float>(320.0f, 240.0f);
	mySpeed = 200.0f; // pixels per second
	myTexture = nullptr;
	mySize = DragonUtilities::Vector2<float>(0.0f, 0.0f);
}

Player::~Player()
{
	myTexture = nullptr;
}

void Player::Initialize(SDL_Texture& aTexture)
{
	myTexture = &aTexture;
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

int Player::GetWidth() const
{
	return myTexture->w;
}

int Player::GetHeight() const
{
	return myTexture->h;
}

void Player::Render(SDL_Renderer& aRenderer)
{
	SDL_FRect playerRect = { myPosition.x, myPosition.y, (float)GetWidth() * 0.5f, (float)GetHeight() * 0.5f };

	// Center the rectangle around the position
	playerRect.x = myPosition.x - playerRect.w * 0.5f;
	playerRect.y = myPosition.y - playerRect.h * 0.5f;

	SDL_RenderTexture(&aRenderer, myTexture, nullptr, &playerRect);
}
