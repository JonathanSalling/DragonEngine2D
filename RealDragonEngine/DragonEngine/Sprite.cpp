#include "Engine.h"
#include "Sprite.h"
#include <SDL3_image/SDL_image.h>
#include "EngineUtilities.h"
#include "Timer.hpp"

DragonEngine::Sprite::Sprite() :
	myTexture(nullptr),
	myPosition(0.f, 0.f),				// top-left of the screen (normalized)
	myScale(1.f, 1.f),					// 1 = native texture size
	myPivot(0.5f, 0.5f),				// center pivot by default
	myRotation(0.0),					// Rotation in degrees (clockwise)
	myColor(255.f, 255.f, 255.f, 255.f), // default to white (no tint)
	myWidth(0),
	myHeight(0),
	myIsSpriteSheet(false),
	myRowsCount(1),
	myColumnsCount(1),
	myFrameCount(1),
	myCurrentFrame(0),
	myTimer(0.f),
	myIsPlaying(true)
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
	SDL_DestroySurface(surface);
	if (!myTexture)
	{
		SDL_Log("Failed to create texture from surface: %s", SDL_GetError());
		return false;
	}

	float w = 0.f;
	float h = 0.f;

	SDL_GetTextureSize(myTexture, &w, &h);

	myWidth = static_cast<int>(w);
	myHeight = static_cast<int>(h);

	SDL_SetTextureBlendMode(myTexture, SDL_BLENDMODE_BLEND);

	return true;
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

void DragonEngine::Sprite::SetScale(const DragonEngine::Vector2<float>& aScale)
{
	myScale = aScale;
}

void DragonEngine::Sprite::SetRotation(const double rotation)
{
	myRotation = rotation;
}

double DragonEngine::Sprite::GetRotation() const
{
	return myRotation;
}

void DragonEngine::Sprite::SetAnimationFPS(float aFramesPerSecond)
{
	myFrameTime = 1.0f / aFramesPerSecond;
}

void DragonEngine::Sprite::SetFrame(int frameIndex)
{
	myCurrentFrame = frameIndex % myFrameCount; // Wrap around if frameIndex exceeds frame count
}

void DragonEngine::Sprite::Play()
{
	myIsPlaying = true;
}

void DragonEngine::Sprite::Pause()
{
	myIsPlaying = false;
}

void DragonEngine::Sprite::Stop()
{
	myIsPlaying = false;
	myCurrentFrame = 0;
	myTimer = 0.f;
}

void DragonEngine::Sprite::SetLooping(bool aShouldLoop)
{
	myLooping = aShouldLoop;
}

void DragonEngine::Sprite::SetColor(const DragonEngine::Color& aColor)
{
	myColor = aColor;
}

DragonEngine::Vector2<float> DragonEngine::Sprite::GetScale() const
{
	return myScale;
}

DragonEngine::Vector2<float> DragonEngine::Sprite::GetNormalizedSize() const
{
	if (!myTexture)
	{
		return { 0.f, 0.f };
	}

	const float renderWidth = static_cast<float>(Engine::GetInstance().GetRenderWidth());
	const float renderHeight = static_cast<float>(Engine::GetInstance().GetRenderHeight());

	const float pixelWidth = myWidth * myScale.x;
	const float pixelHeight = myHeight * myScale.y;

	return { pixelWidth / renderWidth,pixelHeight / renderHeight };
}

// Returns the native texture size in pixels (ignores scale)
DragonEngine::Vector2<int> DragonEngine::Sprite::GetPixelSize() const
{
	return { myWidth, myHeight };
}

// Optional: scaled pixel size
DragonEngine::Vector2<int> DragonEngine::Sprite::GetScaledPixelSize() const
{
	return { static_cast<int>(myWidth * myScale.x), static_cast<int>(myHeight * myScale.y) };
}

void DragonEngine::Sprite::ClearSpriteSheet()
{
	myIsSpriteSheet = false;
}

SDL_FRect DragonEngine::Sprite::GetRect(int frameIndex) const
{
	int row = frameIndex / myColumnsCount;
	int column = frameIndex % myColumnsCount;

	SDL_FRect rect = {
		static_cast<float>(column * myCellWidth),
		static_cast<float>(row * myCellHeight),
		static_cast<float>(myCellWidth),
		static_cast<float>(myCellHeight)
	};

	return rect;
}

void DragonEngine::Sprite::Update(float aDeltaTime)
{
	if (!myIsSpriteSheet || !myIsPlaying)
	{
		return;
	}

	myTimer += aDeltaTime;

	if (myTimer >= myFrameTime)
	{
		myTimer -= myFrameTime;
		myCurrentFrame++;

		if (myCurrentFrame >= myFrameCount)
		{
			if (myLooping)
			{
				myCurrentFrame = 0;
			}
			else
			{
				myCurrentFrame = myFrameCount - 1;
			}
		}
	}
}

void DragonEngine::Sprite::SetSpriteSheet(int aRowCount, int aColumnCount, int aFrameCount)
{
	myCurrentFrame = 0;
	myTimer = 0.f;

	myCellWidth = myWidth / aColumnCount;
	myCellHeight = myHeight / aRowCount;

	if (!myTexture)
	{
		SDL_Log("Cannot set sprite sheet on a sprite without a texture.");
		return;
	}

	myIsSpriteSheet = true;

	myRowsCount = aRowCount;
	myColumnsCount = aColumnCount;

	myFrameCount = aFrameCount;
	myCurrentFrame = 0;
}

void DragonEngine::Sprite::Render() const
{
	if (!myTexture) { return; }

	// SDL_SetTextureColorMod expects Uint8 values for RGB, so we need to convert from float (0-255) to Uint8 (0-255).
	Uint8 red = static_cast<Uint8>(myColor.r);
	Uint8 green = static_cast<Uint8>(myColor.g);
	Uint8 blue = static_cast<Uint8>(myColor.b);
	Uint8 alpha = static_cast<Uint8>(myColor.a);
	SDL_SetTextureColorMod(myTexture, red, green, blue);
	SDL_SetTextureAlphaMod(myTexture, alpha);

	SDL_FRect destinationRect;

	// Convert normalized scale to pixel size
	destinationRect.w = myScale.x * myWidth;
	destinationRect.h = myScale.y * myHeight;

	// Convert normalized screen position to pixel space
	// Pivot shifts the origin inside the sprite
	destinationRect.x = myPosition.x * Engine::GetInstance().GetRenderWidth() - myPivot.x * destinationRect.w;
	destinationRect.y = myPosition.y * Engine::GetInstance().GetRenderHeight() - myPivot.y * destinationRect.h;

	SDL_FPoint center = ToSDLFPoint(myPivot);
	center.x = destinationRect.w * center.x;
	center.y = destinationRect.h * center.y;

	// If this is a sprite sheet, calculate the source rectangle for the current frame
	SDL_FRect* srcRect = nullptr;
	if (myIsSpriteSheet)
	{
		SDL_FRect tempRect;
		tempRect = GetRect(myCurrentFrame);
		srcRect = &tempRect;
	}

	SDL_RenderTextureRotated(
		Engine::GetInstance().GetRenderer(), myTexture, srcRect,
		&destinationRect, myRotation, &center, SDL_FLIP_NONE);
}