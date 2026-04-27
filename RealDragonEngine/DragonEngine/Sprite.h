#pragma once
#include <string>
#include "Vector2.hpp"
#include "Color.h"

struct SDL_Texture;
struct SDL_FRect;

namespace DragonEngine
{
	/**
	 Sprite
	 ------
	 * Represents a 2D image that can be drawn to the screen.
	 *
	 * IMPORTANT DESIGN NOTE:
	 * This class uses NORMALIZED COORDINATES.
	 *
	 * - Position is in screen space from 0 to 1
	 *   (0,0) = top-left corner of the screen
	 *   (1,1) = bottom-right corner of the screen
	 *
	 * - Scale is relative to the texture's original pixel size
	 *   (1,1) = original size
	 *   (0.5,0.5) = half size
	 *   (2,2) = double size
	 *
	 * - Pivot defines the local origin of the sprite
	 *   (0,0) = top-left
	 *   (0.5,0.5) = center
	 *   (1,1) = bottom-right
	 *
	 * The Sprite class hides all SDL rendering details so that
	 * game code never needs to interact with SDL_Renderer directly.
	 */

	class Sprite
	{
		friend class SpriteSheet;

	public:

		// Creates an empty sprite.
		//The sprite will not render until a texture is loaded.
		Sprite();

		// Creates a sprite and loads the texture from the given path.
		explicit Sprite(const std::string& aPath);

		// Destroys the sprite and frees its texture.
		~Sprite();

		// Each sprite owns its own texture; copying is not allowed to avoid crashes.
		Sprite(const Sprite&) = delete;
		Sprite& operator=(const Sprite&) = delete;

		// Sets the position of the sprite in normalized screen space.
		void SetPosition(const DragonEngine::Vector2<float>& aPosition);
		// Gets the position of the sprite in normalized screen space.
		const DragonEngine::Vector2<float>& GetPosition() const;

		// Clears the source rectangle, causing the entire texture to be rendered.
		void ClearSpriteSheet();

		// Updates the sprite's animation frame based on the elapsed time (deltaTime in seconds).
		void Update(float aDeltaTime);

		// Sets the sprite sheet for animation (optional).
		void SetSpriteSheet(int rows, int cols);

		// Renders the sprite to the screen.
		void Render() const;

		// Sets the pivot point of the sprite (normalized 0 to 1).
		void SetPivot(const DragonEngine::Vector2<float>& aPivot);

		// Gets the pivot point of the sprite (normalized 0 to 1).
		DragonEngine::Vector2<float> GetPivot() const;

		// Sets the scale of the sprite (relative to original size).
		void SetScale(const DragonEngine::Vector2<float>& aScale);

		// Sets the color of the sprite (RGB values from 0 to 255).
		void SetColor(const DragonEngine::Color& aColor);

		// Gets the color of the sprite (RGB values from 0 to 255).
		DragonEngine::Color GetColor() const;

		// Gets the scale of the sprite (relative to original size).
		DragonEngine::Vector2<float> GetScale() const;

		// Returns the sprite's size in normalized screen space.
		DragonEngine::Vector2<float> GetNormalizedSize() const;

		// Returns the native texture size in pixels (ignores scale)
		DragonEngine::Vector2<int> GetPixelSize() const;

		// Returns the sprite's size in pixels after applying scale.
		DragonEngine::Vector2<int> GetScaledPixelSize() const;

		// Sets the rotation of the sprite in degrees.
		void SetRotation(const double rotation);

		// Gets the rotation of the sprite in degrees.
		double GetRotation() const;

	private:
		// Loads a texture from the given file path.
		bool LoadTexture(const std::string& aPath);

		// Helper function to calculate the source rectangle for the current animation frame.
		SDL_FRect GetRect(int frameIndex) const;

	private:
		SDL_Texture* myTexture;				// SDL texture owned by this sprite
		DragonEngine::Vector2f myPivot;		// Normalized pivot point
		DragonEngine::Vector2f myPosition;	// Normalized screen position
		DragonEngine::Vector2f myScale;		// Relative scale factor
		DragonEngine::Color myColor;		// Texture color represented as RGB values from 0 to 255 (default is white (255,255,255))
		double myRotation;
		int myWidth;
		int myHeight;

		// Optional animation properties
		int myRowsCount;
		int myColumnsCount;
		bool myIsSpriteSheet = false;
		int myCurrentFrame = 0;
		int myFrameCount = 1;
		float myFrameTime = 0.1f;   // seconds per frame
		float myTimer = 0.0f;
		bool myIsPlaying = true;
		bool myLoop = true;
	};
}