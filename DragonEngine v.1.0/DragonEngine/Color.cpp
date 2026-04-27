#include "Color.h"
#include "SDL3_image/SDL_image.h"
#include <random>


DragonEngine::Color::Color() : r(1.f), g(1.f), b(1.f), a(1.f)
{
}

DragonEngine::Color::Color(const float aRed, const float aGreen, const float aBlue, const float aAlpha) : r(aRed), g(aGreen), b(aBlue), a(aAlpha)
{
}


void DragonEngine::Color::Set(const float aRed, const float aGreen, const float aBlue, const float aAlpha)
{
	r = aRed;
	g = aGreen;
	b = aBlue;
	a = aAlpha;
}

DragonEngine::Color DragonEngine::Color::DisableEffect() const
{
	constexpr float colorProduct = 0.5f; // 0 = fully gray/black, 1 = full color
	constexpr float alphaProduct = 0.8f; // 0 = fully gray/black, 1 = full color
	return { colorProduct * r, colorProduct * g, colorProduct * b, alphaProduct * a };
}

DragonEngine::Color DragonEngine::Color::Random()
{
	static std::mt19937 rng(std::random_device{}());
	static std::uniform_real_distribution<float> dist(0.f, 255.f);

	return { dist(rng), dist(rng), dist(rng), 255.f };
}
