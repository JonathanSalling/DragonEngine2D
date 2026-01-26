#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>
#include "Player.h"
#include "GameWorld.h"

/* We will use this renderer to draw into this window every frame. */
static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
static SDL_Texture* texture = NULL;

GameWorld myGameWorld;
Player myPlayer;

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{
	argv; argc; appstate;  /* avoid unused parameter warnings */

	SDL_SetAppMetadata("Example Renderer Clear", "1.0", "com.example.renderer-clear");

	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	if (!SDL_CreateWindowAndRenderer("DragonEngine", 640 * 2, 480 * 2, SDL_WINDOW_RESIZABLE, &window, &renderer))
	{
		SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}
	SDL_SetRenderLogicalPresentation(renderer, 640, 480, SDL_LOGICAL_PRESENTATION_LETTERBOX);

	/* Load a image */
	texture = IMG_LoadTexture(renderer, "DragonEngine.png");
	if (!texture)
	{
		SDL_Log("Couldn't load icon: %s\n", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	myPlayer.Initialize(*texture);

	return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
	appstate;  /* avoid unused parameter warning */

	myGameWorld.GetInputManager().UpdateEvents(*event);

	if (event->type == SDL_EVENT_QUIT)
	{
		return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
	}
	return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void* appstate)
{
	appstate;  /* avoid unused parameter warning */
	system("cls");

	myGameWorld.GetTimer().Update();
	float deltaTime = myGameWorld.GetTimer().GetDeltaTime();

	myPlayer.Update(deltaTime, myGameWorld.GetInputManager());

	DragonUtilities::InputManager& input = myGameWorld.GetInputManager();

	std::cout << "Player Position: (" << myPlayer.GetPosition().x << ", " << myPlayer.GetPosition().y << ")\n";
	std::cout << "Mouse Position: (" << input.GetMousePosition().x << ", " << input.GetMousePosition().y << ")\n";

	const double now = myGameWorld.GetTimer().GetTotalTime();
	/* choose the color for the frame we will draw. The sine wave trick makes it fade between colors smoothly. */
	const float red = (float)(0.5 + 0.5 * SDL_sin(now));
	const float green = (float)(0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 2 / 3));
	const float blue = (float)(0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 4 / 3));
	SDL_SetRenderDrawColorFloat(renderer, red, green, blue, SDL_ALPHA_OPAQUE_FLOAT);  /* new color, full alpha. */

	/* clear the window to the draw color. */
	SDL_RenderClear(renderer);

	myPlayer.Render(*renderer);

	/* put the newly-cleared rendering on the screen. */
	SDL_RenderPresent(renderer);

	return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
	result; appstate;  /* avoid unused parameter warnings */

	/* SDL will clean up the window/renderer for us. */
	if (renderer) { SDL_DestroyRenderer(renderer); renderer = NULL; }
	if (window) { SDL_DestroyWindow(window);   window = NULL; }
	SDL_Quit();
}