#pragma once
#include <string>
#include "Color.h"
#include "Vector2.hpp"

struct SDL_Texture;
struct TTF_Font;

namespace DragonEngine
{
	// The Text class represents a renderable text object in the game world.
	class Text
	{
    public:
        // Creates a text object using a string, font size, and font file path.
        // The font is loaded once and reused for this text instance
        Text(const std::string& aText, float aFontSize, const std::string& aFontPath = "Fonts/arial.ttf");
        ~Text();

        // Deleted copy and move constructors and assignment operators to prevent copying or moving the sprite,
        // which would cause issues with the owned SDL_Texture and TTF_Font
        Text(const Text&) = delete;
        Text& operator=(const Text&) = delete;
        Text(Text&&) = delete;
        Text& operator=(Text&&) = delete;

        // Sets the displayed text string.
        // Marks the texture as "dirty", will be regenerated on next render (Expensive)
        void SetText(const std::string& aText);

        // Sets the text color.
        // Marks the texture as "dirty", will be regenerated on next render (Expensive)
        void SetColor(const Color& aColor);

        // Sets the pivot point (origin) of the text in normalized space (0–1).
        // Does NOT trigger texture rebuild since it only affects rendering.
        void SetPivot(const Vector2f& aPivot);

		// Sets the position of the text in normalized screen space (0–1).
        void SetPosition(const Vector2f& aPosition);
		// Sets the scale of the text. (1,1) is normal size.
        void SetScale(const Vector2f& aScale);

        // Renders the text to the screen.
        // If the text is marked dirty, the texture will be rebuilt first
        void Render();

    private:
		// Rebuilds the SDL_Texture from the current text, font, and color.
        void UpdateTexture();

        std::string myText;
        TTF_Font* myFont = nullptr;
        SDL_Texture* myTexture = nullptr;

        Color myColor = Color::White;

        Vector2f myPosition;
        Vector2f myScale = { 1.f, 1.f };
        Vector2f myPivot = { 0.f, 0.f };

        int myWidth = 0;
        int myHeight = 0;

        bool myIsDirty = false;
	};
}

