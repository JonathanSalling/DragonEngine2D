#pragma once
#include "EngineVector4.hpp"

struct SDL_Color;

namespace DragonEngine
{
	class Color
	{
	public:
		Color();

		Color(float aRed, float aGreen, float aBlue, float aAlpha);

		void Set(float aRed, float aGreen, float aBlue, float aAlpha);

		DragonEngine::Vector4f AsVec4();

		unsigned int AsHex();

		DragonEngine::Color DisableEffect() const;

		SDL_Color AsSDLColor() const;

		float myRed;
		float myGreen;
		float myBlue;
		float myAlpha;
	};
}