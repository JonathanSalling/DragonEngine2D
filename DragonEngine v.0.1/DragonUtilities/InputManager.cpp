#include "pch.h"
#include "InputManager.h"

bool DragonUtilities::InputManager::IsKeyDown(SDL_Scancode aKeyCode) const
{
	aKeyCode;
	return false;
}

bool DragonUtilities::InputManager::IsKeyPressed(SDL_Scancode aKeyCode) const
{
	aKeyCode;
	return false;
}

bool DragonUtilities::InputManager::IsKeyReleased(SDL_Scancode aKeyCode) const
{
	aKeyCode;
	return false;
}

void DragonUtilities::InputManager::SetMousePos(SDL_Window* aWindow, SDL_Point aPoint) const
{
	aWindow; aPoint;
}

SDL_Point DragonUtilities::InputManager::GetMousePosition() const
{
	return SDL_Point();
}
int DragonUtilities::InputManager::GetMouseWheelDelta() const
{
	return 0;
}

bool DragonUtilities::InputManager::UpdateEvents(const SDL_Event& aEvent)
{
	aEvent;
	return false;
}
SDL_Point DragonUtilities::InputManager::GetMouseDelta() const
{
	return SDL_Point();
}