#pragma once
#include "Vector2.hpp"
#include <SDL3/SDL_rect.h>


namespace DragonEngine
{
	// Convert Vector2 to SDL_Point
	SDL_Point ToSDLPoint(const DragonEngine::Vector2<float>& aVector)
	{
		return SDL_Point{ static_cast<int>(std::round(aVector.x)), static_cast<int>(std::round(aVector.y)) };
	}

	// Convert Vector2 to SDL_FPoint
	SDL_FPoint ToSDLFPoint(const DragonEngine::Vector2<float>& aVector)
	{
		return SDL_FPoint{ aVector.x, aVector.y };
	}

	// Convert SDL_Point to Vector2f
	Vector2f ToVector2f(const SDL_Point& aPoint)
	{
		return Vector2f{ static_cast<float>(aPoint.x), static_cast<float>(aPoint.y) };
	}

	// Convert SDL_FPoint to Vector2f
	Vector2f ToVector2f(const SDL_FPoint& aPoint)
	{
		return Vector2f{ aPoint.x, aPoint.y };
	}
};

