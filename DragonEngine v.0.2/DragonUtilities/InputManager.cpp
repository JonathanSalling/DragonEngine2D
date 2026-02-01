#include "pch.h"
#include "InputManager.h"

bool DragonUtilities::InputManager::IsKeyDown(SDL_Scancode aKeyCode) const
{
	return myKeyInfo[aKeyCode].isDown;
}

bool DragonUtilities::InputManager::IsKeyPressed(SDL_Scancode aKeyCode) const
{
	return myKeyInfo[aKeyCode].isPressed;
}

bool DragonUtilities::InputManager::IsKeyReleased(SDL_Scancode aKeyCode) const
{
	return myKeyInfo[aKeyCode].isReleased;
}

void DragonUtilities::InputManager::SetMousePos(SDL_Window* aWindow, SDL_Point aPoint) const
{
	if (!aWindow) return;  // Safety check
	SDL_WarpMouseInWindow(aWindow, (float)aPoint.x, (float)aPoint.y);
}

SDL_Point DragonUtilities::InputManager::GetMousePosition() const
{
	return myMousePosition;
}
int DragonUtilities::InputManager::GetMouseWheelDelta() const
{
	return myMouseWheelDelta;
}

bool DragonUtilities::InputManager::UpdateEvents(const SDL_Event& event)
{
	myMouseWheelDelta = 0;

	for (auto& key : myKeyInfo)
	{
		key.isPressed = false;
		key.isReleased = false;
	}

	switch (event.type)
	{
	case SDL_EVENT_KEY_DOWN:
	{
		myKeyInfo[event.key.scancode].isReleased = false;

		auto& key = myKeyInfo[event.key.scancode];
		if (!key.isDown)
		{
			key.isPressed = true;
		}
		key.isDown = true;
		break;
	}
	case SDL_EVENT_KEY_UP:
	{
		auto& key = myKeyInfo[event.key.scancode];
		key.isDown = false;
		key.isReleased = true;
		break;
	}

	case SDL_EVENT_MOUSE_MOTION:
		myPreviousMPos = myMousePosition;
		myMousePosition.x = (int)event.motion.x;
		myMousePosition.y = (int)event.motion.y;
		break;

	case SDL_EVENT_MOUSE_WHEEL:
		myMouseWheelDelta += (int)event.wheel.y;
		break;

	case SDL_EVENT_QUIT:
		return false;
	}

	return true;
}
SDL_Point DragonUtilities::InputManager::GetMouseDelta() const
{
	SDL_Point delta;
	delta.x = myMousePosition.x - myPreviousMPos.x;
	delta.y = myMousePosition.y - myPreviousMPos.y;
	return delta;
}