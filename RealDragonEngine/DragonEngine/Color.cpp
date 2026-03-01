#include "Color.h"
#include "SDL3_image/SDL_image.h"
#include <random>


DragonEngine::Color::Color() : r(1.f), g(1.f), b(1.f), a(1.f)
{
}

DragonEngine::Color::Color(float aRed, float aGreen, float aBlue, float aAlpha) : r(aRed), g(aGreen), b(aBlue), a(aAlpha)
{
}


void DragonEngine::Color::Set(float aRed, float aGreen, float aBlue, float aAlpha)
{
	r = aRed;
	g = aGreen;
	b = aBlue;
	a = aAlpha;
}

DragonEngine::Color DragonEngine::Color::DisableEffect() const
{
	float colorProduct = 0.5f; // 0 = fully gray/black, 1 = full color
	float alphaProduct = 0.8f; // 0 = fully gray/black, 1 = full color
	return Color(colorProduct * r, colorProduct * g, colorProduct * b, alphaProduct * a);
}

DragonEngine::Color DragonEngine::Color::Random()
{
	static std::mt19937 rng(std::random_device{}());
	static std::uniform_real_distribution<float> dist(0.f, 255.f);

	return Color(dist(rng), dist(rng), dist(rng), 255.f);
}
