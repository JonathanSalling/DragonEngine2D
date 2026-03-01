#pragma once
#include <array>
#include "Vector2.hpp"

struct SDL_Window;
union SDL_Event;
enum SDL_Scancode : int;


namespace DragonUtilities
{
	enum class MouseButton
	{
		LEFT,
		RIGHT,
		MIDDLE
	};

	enum class Key
	{
		UNKNOWN,
		UP, DOWN, LEFT, RIGHT,
		A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
		NUM1, NUM2, NUM3, NUM4, NUM5, NUM6, NUM7, NUM8, NUM9, NUM0,
		RETURN, ESCAPE, BACKSPACE, TAB, SPACE, LSHIFT, RSHIFT, LCTRL, RCTRL,
		CAPSLOCK,
		F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12
	};



	class InputManager
	{
		struct KeyInfo
		{
			bool isDown = false;
			bool isPressed = false;
			bool isReleased = false;
		};

		struct MouseButtonInfo
		{
			bool isDown = false;
			bool isPressed = false;
			bool isReleased = false;
		};

	public:
		//  Update input states
		bool Update();

		// Returns true while the key is held down
		bool IsKeyDown(DragonUtilities::Key aKey) const;

		// Returns true only on the frame the key was pressed
		bool IsKeyPressed(DragonUtilities::Key aKey) const;

		// Returns true only on the frame the key was released
		bool IsKeyReleased(DragonUtilities::Key aKey) const;

		// Returns true while the mouse button is held down
		bool IsMouseDown(MouseButton button) const;

		// Returns true only on the frame the mouse button was pressed
		bool IsMousePressed(MouseButton button) const;
		
		// Returns true only on the frame the mouse button was released
		bool IsMouseReleased(MouseButton button) const;

		// Current mouse position in window coordinates
		DragonUtilities::Vector2<int> GetMousePosition() const;

		// Mouse movement delta since last frame
		DragonUtilities::Vector2<int> GetMouseDelta() const;

		// Mouse wheel delta since last frame
		int GetMouseWheelDelta() const;

		//  Set mouse position in window coordinates
		void SetMousePosition(Vector2<int> aPosition);

	private:
		DragonUtilities::Vector2<int> myMousePosition;
		DragonUtilities::Vector2<int> myPreviousMousePosition;
		int myMouseWheelDelta;
		std::array<KeyInfo, 256> myKeyInfo;
		MouseButtonInfo myMouseButtons[3]; // LEFT=0, RIGHT=1, MIDDLE=2
	};
}