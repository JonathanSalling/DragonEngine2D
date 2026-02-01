#include "Engine.h"
#include "Sprite.h"
#include <SDL3_image/SDL_image.h>

DragonEngine::Sprite::Sprite() : 
	myTexture(nullptr), 
	myPosition(0.f, 0.f),	// top-left of the screen (normalized)
	myScale(1.f, 1.f),		// 1 = native texture size
	myPivot(0.5f, 0.5f)		// center pivot by default
{
}

DragonEngine::Sprite::Sprite(const std::string& aPath) : Sprite()
{
	if (!LoadTexture(aPath))
	{
		SDL_Log("Sprite failed to load: %s", aPath.c_str());
	}
}

DragonEngine::Sprite::~Sprite()
{
	if (myTexture)
	{
		SDL_DestroyTexture(myTexture);
		myTexture = nullptr;
	}
}

void DragonEngine::Sprite::SetPosition(const DragonEngine::Vector2<float>& aPosition)
{
	myPosition = aPosition;
}

const DragonEngine::Vector2<float>& DragonEngine::Sprite::GetPosition() const
{
	return myPosition;
}

bool DragonEngine::Sprite::LoadTexture(const std::string& aPath)
{
	// Textures must be created using the engine's renderer.
	// This keeps all SDL rendering ownership inside the Engine.

	SDL_Surface* surface = IMG_Load(aPath.c_str());
	if (!surface)
	{
		SDL_Log("Failed to load sprite %s: %s", aPath.c_str(), SDL_GetError());
		return false;
	}

	SDL_Renderer* renderer = Engine::GetInstance().GetRenderer();
	myTexture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!myTexture)
	{
		SDL_Log("Failed to create texture from surface: %s", SDL_GetError());
	}

	SDL_DestroySurface(surface);
	return myTexture != nullptr;
}

void DragonEngine::Sprite::Render() const
{
	if (!myTexture) { return; }

	SDL_FRect destinationRect;

	// Convert normalized scale to pixel size
	destinationRect.w = static_cast<float>(myScale.x) * myTexture->w;
	destinationRect.h = static_cast<float>(myScale.y) * myTexture->h;

	// Convert normalized screen position to pixel space
	// Pivot shifts the origin inside the sprite
	destinationRect.x = myPosition.x * Engine::GetInstance().GetRenderWidth() - myPivot.x * destinationRect.w;
	destinationRect.y = myPosition.y * Engine::GetInstance().GetRenderHeight() - myPivot.y * destinationRect.h;

	SDL_RenderTexture(Engine::GetInstance().GetRenderer(), myTexture, nullptr, &destinationRect);
}

void DragonEngine::Sprite::SetPivot(const DragonEngine::Vector2<float>& aPivot)
{
	myPivot = aPivot;
}

void DragonEngine::Sprite::SetScale(const DragonEngine::Vector2<float>& aSize)
{
	myScale = aSize;
}

DragonEngine::Vector2<float> DragonEngine::Sprite::GetScale() const
{
	return myScale;
}
