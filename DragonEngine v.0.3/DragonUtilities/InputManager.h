#pragma once
#include <array>
#include <SDL3/SDL_events.h>

namespace DragonUtilities
{
	class InputManager
	{
		struct KeyInfo
		{
			bool isDown = false;
			bool isPressed = false;
			bool isReleased = false;
		};

	public:
		//  Update input states
		bool UpdateEvents(const SDL_Event& aEvent);

		// Returns true while the key is held down
		bool IsKeyDown(SDL_Scancode aKey) const;

		// Returns true only on the frame the key was pressed
		bool IsKeyPressed(SDL_Scancode aKey) const;

		// Returns true only on the frame the key was released
		bool IsKeyReleased(SDL_Scancode aKey) const;

		// Current mouse position in window coordinates
		SDL_Point GetMousePosition() const;

		// Mouse movement delta since last frame
		SDL_Point GetMouseDelta() const;

		// Mouse wheel delta since last frame
		int GetMouseWheelDelta() const;

		//  Set mouse position in window coordinates
		void SetMousePos(SDL_Window* aWindow, SDL_Point aPoint) const;

	private:
		SDL_Point myMousePosition;
		SDL_Point myPreviousMPos;
		int myMouseWheelDelta;
		std::array<KeyInfo, 255> myKeyInfo;
	};
}