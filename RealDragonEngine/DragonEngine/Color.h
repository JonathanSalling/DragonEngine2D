#pragma once
#include "EngineVector4.hpp"

namespace DragonEngine
{
	class Color
	{
	public:
		Color();
		Color(float aRed, float aGreen, float aBlue, float aAlpha);

		void Set(float aRed, float aGreen, float aBlue, float aAlpha);
		Color DisableEffect() const;

		static Color Random();

		static const Color Red;
		static const Color Green;
		static const Color Blue;
		static const Color White;
		static const Color Black;

		float r, g, b, a;
	};
	inline const Color Color::Black{ 0.f, 0.f, 0.f, 255.f };
	inline const Color Color::Blue{ 0.f, 0.f, 255.f, 255.f };
	inline const Color Color::Green{ 0.f, 255.f, 0.f, 255.f };
	inline const Color Color::Red{ 255.f, 0.f, 0.f, 255.f };
	inline const Color Color::White{ 255.f, 255.f, 255.f, 255.f };
}