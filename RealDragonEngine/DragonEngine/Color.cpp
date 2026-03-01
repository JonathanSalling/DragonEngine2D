#include "Color.h"
#include "SDL3_image/SDL_image.h"


DragonEngine::Color::Color() : myRed(0.f), myGreen(0.f), myBlue(0.f), myAlpha(0.f)
{
}

DragonEngine::Color::Color(float aRed, float aGreen, float aBlue, float aAlpha) : myRed(aRed), myGreen(aGreen), myBlue(aBlue), myAlpha(aAlpha)
{
}


void DragonEngine::Color::Set(float aRed, float aGreen, float aBlue, float aAlpha)
{
	myRed = aRed;
	myGreen = aGreen;
	myBlue = aBlue;
	myAlpha = aAlpha;
}

DragonEngine::Vector4f DragonEngine::Color::AsVec4()
{
	return DragonEngine::Vector4f(myRed, myGreen, myBlue, myAlpha);
}

unsigned int DragonEngine::Color::AsHex()
{
	unsigned char r = static_cast<unsigned char>(myRed * 255.0f);
	unsigned char g = static_cast<unsigned char>(myGreen * 255.0f);
	unsigned char b = static_cast<unsigned char>(myBlue * 255.0f);
	unsigned char a = static_cast<unsigned char>(myAlpha * 255.0f);

	unsigned int final = 0;
	final |= (a << 24);
	final |= (r << 16);
	final |= (g << 8);
	final |= (b);
	return final;
}

DragonEngine::Color DragonEngine::Color::DisableEffect() const
{
	float colorProduct = 0.5f * 255.f; // 0 = fully gray/black, 1 = full color
	float alphaProduct = 0.8f * 255.f; // 0 = fully gray/black, 1 = full color
	return Color(colorProduct, colorProduct, colorProduct, alphaProduct);
}

DragonEngine::Color Random()
{
	return DragonEngine::Color{
		static_cast<float>(rand()) / RAND_MAX,
		static_cast<float>(rand()) / RAND_MAX,
		static_cast<float>(rand()) / RAND_MAX,
		1.f
	};
}


SDL_Color DragonEngine::Color::AsSDLColor() const
{
	return SDL_Color{
	static_cast<uint8_t>(myRed * 255.0f),
	static_cast<uint8_t>(myGreen * 255.0f),
	static_cast<uint8_t>(myBlue * 255.0f),
	static_cast<uint8_t>(myAlpha * 255.0f)
	};
}
