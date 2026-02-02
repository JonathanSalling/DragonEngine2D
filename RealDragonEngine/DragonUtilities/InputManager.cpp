#include "pch.h"
#include "InputManager.h"
#include <SDL3/SDL_rect.h>

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

bool DragonUtilities::InputManager::UpdateEvents(const SDL_Event& aEvent)
{
	myMouseWheelDelta = 0;

	for (KeyInfo& key : myKeyInfo)
	{
		key.isPressed = false;
		key.isReleased = false;
	}

	switch (aEvent.type)
	{
	case SDL_EVENT_KEY_DOWN:
	{
		if (myKeyInfo[aEvent.key.scancode].isDown == false)
		{
			myKeyInfo[aEvent.key.scancode].isPressed = true;
		}
		myKeyInfo[aEvent.key.scancode].isDown = true;
		break;
	}
	case SDL_EVENT_KEY_UP:
	{
		myKeyInfo[aEvent.key.scancode].isDown = false;
		myKeyInfo[aEvent.key.scancode].isReleased = true;
		break;
	}

	case SDL_EVENT_MOUSE_MOTION:
		myPreviousMPos = myMousePosition;
		myMousePosition.x = static_cast<int>(aEvent.motion.x);
		myMousePosition.y = static_cast<int>(aEvent.motion.y);
		break;

	case SDL_EVENT_MOUSE_WHEEL:
		myMouseWheelDelta += static_cast<int>(aEvent.wheel.y);
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