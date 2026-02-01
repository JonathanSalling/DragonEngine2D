#pragma once

#include <Vector2.hpp>
#include <InputManager.h>
#include <SDL3_image/SDL_image.h>
#include <Sprite.h>

class Player
{
public:
	Player();
	~Player();
	void Initialize();
	void Update(float deltaTime, const DragonUtilities::InputManager& aInputManager);

	void SetPosition(const DragonUtilities::Vector2<float>& aPosition);
	void SetVelocity(const DragonUtilities::Vector2<float>& aVelocity);
	const DragonUtilities::Vector2<float>& GetPosition() const;
	const DragonUtilities::Vector2<float>& GetVelocity() const;

	float GetWidth() const;
	float GetHeight() const;

	float GetSpeed() const { return mySpeed; }

	void Render();


private:
	DragonUtilities::Vector2<float> myPosition;
	DragonUtilities::Vector2<float> myVelocity;
	float mySpeed;

	DragonEngine::Sprite* myTexture;
};

