#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL_main.h>
#include <Game.h>

static Game* game = nullptr;

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{
	argv; argc; appstate;  /* avoid unused parameter warnings */

	game = new Game();

	return (SDL_AppResult)game->Init();  /* carry on with the program! */
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
	appstate;  /* avoid unused parameter warning */

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

	game->UpdateInput();
	game->UpdateCallBack();

	return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
	result; appstate;  /* avoid unused parameter warnings */

	game->ShutdownGame();
}