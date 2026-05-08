#include "InputManager.h"
#include <SDL3/SDL.h>
#include <unordered_map>

namespace DragonEngine {

	// Map Key enum to SDL scancodes internally
	static const std::unordered_map<Key, SDL_Scancode> keyMap{
		{ Key::UP, SDL_SCANCODE_UP },
		{ Key::DOWN, SDL_SCANCODE_DOWN },
		{ Key::LEFT, SDL_SCANCODE_LEFT },
		{ Key::RIGHT, SDL_SCANCODE_RIGHT },
		{ Key::SPACE, SDL_SCANCODE_SPACE },
		{ Key::ESCAPE, SDL_SCANCODE_ESCAPE },
		{ Key::A, SDL_SCANCODE_A },
		{ Key::B, SDL_SCANCODE_B },
		{ Key::C, SDL_SCANCODE_C },
		{ Key::D, SDL_SCANCODE_D },
		{ Key::E, SDL_SCANCODE_E },
		{ Key::F, SDL_SCANCODE_F },
		{ Key::G, SDL_SCANCODE_G },
		{ Key::H, SDL_SCANCODE_H },
		{ Key::I, SDL_SCANCODE_I },
		{ Key::J, SDL_SCANCODE_J },
		{ Key::K, SDL_SCANCODE_K },
		{ Key::L, SDL_SCANCODE_L },
		{ Key::M, SDL_SCANCODE_M },
		{ Key::N, SDL_SCANCODE_N },
		{ Key::O, SDL_SCANCODE_O },
		{ Key::P, SDL_SCANCODE_P },
		{ Key::Q, SDL_SCANCODE_Q },
		{ Key::R, SDL_SCANCODE_R },
		{ Key::S, SDL_SCANCODE_S },
		{ Key::T, SDL_SCANCODE_T },
		{ Key::U, SDL_SCANCODE_U },
		{ Key::V, SDL_SCANCODE_V },
		{ Key::W, SDL_SCANCODE_W },
		{ Key::X, SDL_SCANCODE_X },
		{ Key::Y, SDL_SCANCODE_Y },
		{ Key::Z, SDL_SCANCODE_Z },
		{ Key::NUM1, SDL_SCANCODE_1 },
		{ Key::NUM2, SDL_SCANCODE_2 },
		{ Key::NUM3, SDL_SCANCODE_3 },
		{ Key::NUM4, SDL_SCANCODE_4 },
		{ Key::NUM5, SDL_SCANCODE_5 },
		{ Key::NUM6, SDL_SCANCODE_6 },
		{ Key::NUM7, SDL_SCANCODE_7 },
		{ Key::NUM8, SDL_SCANCODE_8 },
		{ Key::NUM9, SDL_SCANCODE_9 },
		{ Key::NUM0, SDL_SCANCODE_0 },
		{ Key::RETURN, SDL_SCANCODE_RETURN },
		{ Key::BACKSPACE, SDL_SCANCODE_BACKSPACE },
		{ Key::TAB, SDL_SCANCODE_TAB },
		{ Key::SPACE, SDL_SCANCODE_SPACE },
		{ Key::LSHIFT, SDL_SCANCODE_LSHIFT },
		{ Key::RSHIFT, SDL_SCANCODE_RSHIFT },
		{ Key::LCTRL, SDL_SCANCODE_LCTRL },
		{ Key::RCTRL, SDL_SCANCODE_RCTRL },
		{ Key::CAPSLOCK, SDL_SCANCODE_CAPSLOCK },
		{ Key::F1, SDL_SCANCODE_F1 },
		{ Key::F2, SDL_SCANCODE_F2 },
		{ Key::F3, SDL_SCANCODE_F3 },
		{ Key::F4, SDL_SCANCODE_F4 },
		{ Key::F5, SDL_SCANCODE_F5 },
		{ Key::F6, SDL_SCANCODE_F6 },
		{ Key::F7, SDL_SCANCODE_F7 },
		{ Key::F8, SDL_SCANCODE_F8 },
		{ Key::F9, SDL_SCANCODE_F9 },
		{ Key::F10, SDL_SCANCODE_F10 },
		{ Key::F11, SDL_SCANCODE_F11 },
		{ Key::F12, SDL_SCANCODE_F12 }
	};

	bool InputManager::IsKeyDown(Key key) const
	{
		auto iterator = keyMap.find(key);
		if (iterator == keyMap.end()) return false;
		return myKeyInfo[iterator->second].isDown;
	}

	bool InputManager::IsKeyPressed(Key key) const
	{
		auto iterator = keyMap.find(key);
		if (iterator == keyMap.end()) return false;
		return myKeyInfo[iterator->second].isPressed;
	}

	bool InputManager::IsKeyReleased(Key key) const
	{
		auto iterator = keyMap.find(key);
		if (iterator == keyMap.end()) return false;
		return myKeyInfo[iterator->second].isReleased;
	}

	bool InputManager::IsMouseDown(MouseButton button) const
	{
		return myMouseButtons[static_cast<int>(button)].isDown;
	}

	bool InputManager::IsMousePressed(MouseButton button) const
	{
		return myMouseButtons[static_cast<int>(button)].isPressed;
	}

	bool InputManager::IsMouseReleased(MouseButton button) const
	{
		return myMouseButtons[static_cast<int>(button)].isReleased;
	}

	DragonEngine::Vector2<float> InputManager::GetMousePosition() const
	{
		return myMousePosition;
	}

	DragonEngine::Vector2<float> InputManager::GetMouseDelta() const
	{
		return { myMousePosition.x - myPreviousMousePosition.x,
				 myMousePosition.y - myPreviousMousePosition.y };
	}

	void InputManager::SetMousePosition(DragonEngine::Vector2<float> aPosition)
	{
		myMousePosition = aPosition;
		SDL_WarpMouseInWindow(SDL_GetKeyboardFocus(), static_cast<float>(aPosition.x), static_cast<float>(aPosition.y));
	}

	int InputManager::GetMouseWheelDelta() const
	{
		return myMouseWheelDelta;
	}

	bool InputManager::Update()
	{
		myMouseWheelDelta = 0;

		// Reset pressed/released at start of frame
		for (auto& key : myKeyInfo)
		{
			key.isPressed = false;
			key.isReleased = false;
		}

		// Make sure SDL events are pumped
		SDL_PumpEvents();

		// Get current keyboard state
		const bool* state = SDL_GetKeyboardState(nullptr);

		for (auto& [keyEnum, scancode] : keyMap)
		{
			bool wasDown = myKeyInfo[scancode].isDown;
			bool isDown = state[scancode];

			if (isDown)
			{

				myKeyInfo[scancode].isPressed = (!wasDown && isDown);
			}

			// Calculate pressed/released BEFORE updating isDown
			myKeyInfo[scancode].isReleased = (wasDown && !isDown);

			// Update isDown
			myKeyInfo[scancode].isDown = isDown;
		}
		myPreviousMousePosition = myMousePosition;
		SDL_MouseButtonFlags mouseState = SDL_GetMouseState(&myMousePosition.x, &myMousePosition.y);
		for (int i = 0; i < 3; ++i) // LEFT=0, RIGHT=1, MIDDLE=2
		{
			bool wasDown = myMouseButtons[i].isDown;
			bool isDown = (mouseState & SDL_BUTTON_MASK(i + 1)) != 0;

			myMouseButtons[i].isPressed = (!wasDown && isDown);
			myMouseButtons[i].isReleased = (wasDown && !isDown);
			myMouseButtons[i].isDown = isDown;
		}

		// Mouse events / quit
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_EVENT_MOUSE_WHEEL:
				myMouseWheelDelta += static_cast<int>(event.wheel.y);
				break;
			case SDL_EVENT_QUIT:
				// Handle quit if needed
				break;
			}
		}

		return true;
	}
}