#include "Engine.h"
#include "Text.h"

#include <cassert>
#include <SDL3_ttf/SDL_ttf.h>

DragonEngine::Text::Text(const std::string& aText, float aFontSize, const std::string& aFontPath) : myText(aText)
{
	myFont = TTF_OpenFont(aFontPath.c_str(), aFontSize);
	if (!myFont)
	{
		SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Failed to load %s: %s", aFontPath.c_str(), SDL_GetError());
		assert(false && "Font failed to load");
		return;
	}

	myIsDirty = true;
}

DragonEngine::Text::~Text()
{
	if (myTexture)
	{
		SDL_DestroyTexture(myTexture);
	}

	if (myFont)
	{
		TTF_CloseFont(myFont);
	}
}

void DragonEngine::Text::SetText(const std::string& aText)
{
	myText = aText;
	myIsDirty = true;
}

void DragonEngine::Text::SetColor(const Color& aColor)
{
	myColor = aColor;
	myIsDirty = true;
}

void DragonEngine::Text::SetPivot(const Vector2f& aPivot)
{
	myPivot = aPivot;
}

void DragonEngine::Text::SetPosition(const Vector2f& aPosition)
{
	myPosition = aPosition;
}

void DragonEngine::Text::SetScale(const Vector2f& aScale)
{
	myScale = aScale;
}

void DragonEngine::Text::UpdateTexture()
{
	if (myTexture)
	{
		SDL_DestroyTexture(myTexture);
		myTexture = nullptr;
	}

	myWidth = 0;
	myHeight = 0;

	if (myText.empty() || !myFont)
	{
		return;
	}

	SDL_Color color = { static_cast<Uint8>(myColor.r), static_cast<Uint8>(myColor.g), static_cast<Uint8>(myColor.b), static_cast<Uint8>(myColor.a) };

	SDL_Surface* surface = TTF_RenderText_Blended(myFont, myText.c_str(), 0, color);
	if (!surface)
	{
		SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Failed to create (%s) text surface: %s", myText.c_str(), SDL_GetError());
		return;
	}

	myTexture = SDL_CreateTextureFromSurface(Engine::GetInstance().GetRenderer(), surface);
	myWidth = surface->w;
	myHeight = surface->h;

	SDL_DestroySurface(surface);

	if (!myTexture)
	{
		SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Failed to create texture from surface: %s", SDL_GetError());
		return;
	}
}

void DragonEngine::Text::Render()
{
	if (myIsDirty)
	{
		UpdateTexture();
		myIsDirty = false;
	}

	if (!myTexture)
	{
		return;
	}

	SDL_FRect dest;

	float renderW = Engine::GetInstance().GetRenderWidth();
	float renderH = Engine::GetInstance().GetRenderHeight();

	dest.x = myPosition.x * renderW;
	dest.y = myPosition.y * renderH;
	dest.w = myWidth * myScale.x;
	dest.h = myHeight * myScale.y;

	dest.x -= myPivot.x * dest.w;
	dest.y -= myPivot.y * dest.h;

	SDL_RenderTexture(Engine::GetInstance().GetRenderer(), myTexture, nullptr, &dest);
}