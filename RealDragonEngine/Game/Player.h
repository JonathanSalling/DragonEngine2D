#pragma once

#include "DragonUtilities/Vector2.hpp"
#include <SDL3_image/SDL_image.h>
#include "DragonUtilities/InputManager.h"

class Player
{
public:
	Player();
	~Player();
	void Initialize(SDL_Texture& aTexture);
	void Update(float deltaTime, const DragonUtilities::InputManager& aInputManager);

	void SetPosition(const DragonUtilities::Vector2<float>& aPosition);
	void SetVelocity(const DragonUtilities::Vector2<float>& aVelocity);
	const DragonUtilities::Vector2<float>& GetPosition() const;
	const DragonUtilities::Vector2<float>& GetVelocity() const;

	int GetWidth() const;
	int GetHeight() const;

	float GetSpeed() const { return mySpeed; }

	void Render(SDL_Renderer& aRenderer);


private:
	DragonUtilities::Vector2<float> myPosition;
	DragonUtilities::Vector2<float> myVelocity;
	float mySpeed;

	SDL_Texture* myTexture;
	DragonUtilities::Vector2<float> mySize;
};

