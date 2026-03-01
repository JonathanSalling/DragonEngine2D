#include "Engine.h"
#include "Sprite.h"
#include <SDL3_image/SDL_image.h>
#include "EngineUtilities.h"

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

void DragonEngine::Sprite::SetPivot(const DragonEngine::Vector2<float>& aPivot)
{
	myPivot = aPivot;
}

DragonEngine::Vector2<float> DragonEngine::Sprite::GetPivot() const
{
	return myPivot;
}

DragonEngine::Color DragonEngine::Sprite::GetColor() const
{
	return myColor;
}

void DragonEngine::Sprite::SetScale(const DragonEngine::Vector2<float>& aSize)
{
	myScale = aSize;
}

void DragonEngine::Sprite::SetRotation(const double rotation)
{
	myRotation = rotation;
}

const double DragonEngine::Sprite::GetRotation() const
{
	return myRotation;
}

void DragonEngine::Sprite::SetColor(const DragonEngine::Color& aColor)
{
	myColor = aColor;

	// SDL_SetTextureColorMod expects Uint8 values for RGB, so we need to convert from float (0-255) to Uint8 (0-255).
	Uint8 red = static_cast<Uint8>(myColor.myRed);
	Uint8 green = static_cast<Uint8>(myColor.myGreen);
	Uint8 blue = static_cast<Uint8>(myColor.myBlue);
	Uint8 alpha = static_cast<Uint8>(myColor.myAlpha);
	SDL_SetTextureColorMod(myTexture, red, green, blue);
	SDL_SetTextureAlphaMod(myTexture, alpha);

	if (alpha < 255)
	{
		SDL_BlendMode currentBlend;
		if (SDL_GetTextureBlendMode(myTexture, &currentBlend) == 0 && currentBlend != SDL_BLENDMODE_BLEND)
		{
			SDL_SetTextureBlendMode(myTexture, SDL_BLENDMODE_BLEND);
		}
	}
}

DragonEngine::Vector2<float> DragonEngine::Sprite::GetScale() const
{
	return myScale;
}

DragonEngine::Vector2<float> DragonEngine::Sprite::GetSize() const
{
	if (!myTexture)
	{
		return { 0.f, 0.f };
	}

	const float renderWidth = static_cast<float>(Engine::GetInstance().GetRenderWidth());
	const float renderHeight = static_cast<float>(Engine::GetInstance().GetRenderHeight());

	const float pixelWidth = myTexture->w * myScale.x;
	const float pixelHeight = myTexture->h * myScale.y;

	return { pixelWidth / renderWidth,pixelHeight / renderHeight };
}

void DragonEngine::Sprite::Render() const
{
	if (!myTexture) { return; }

	SDL_FRect destinationRect;

	// Convert normalized scale to pixel size
	destinationRect.w = myScale.x * myTexture->w;
	destinationRect.h = myScale.y * myTexture->h;

	// Convert normalized screen position to pixel space
	// Pivot shifts the origin inside the sprite
	destinationRect.x = myPosition.x * Engine::GetInstance().GetRenderWidth() - myPivot.x * destinationRect.w;
	destinationRect.y = myPosition.y * Engine::GetInstance().GetRenderHeight() - myPivot.y * destinationRect.h;

	SDL_FPoint center = ToSDLFPoint(myPivot);
	center.x = destinationRect.w * center.x;
	center.y = destinationRect.h * center.y;

	SDL_RenderTextureRotated(Engine::GetInstance().GetRenderer(), myTexture, nullptr, &destinationRect, myRotation, &center, SDL_FLIP_NONE);
}