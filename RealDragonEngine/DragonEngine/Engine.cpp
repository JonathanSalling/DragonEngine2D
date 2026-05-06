#include "Engine.h"
#include <SDL3/SDL_render.h>
#include "SDL3/SDL_log.h"
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "Debug.h"

#define SAFE_DELETE(aPointer) delete aPointer; aPointer = nullptr;

DragonEngine::Engine::Engine() : myRenderer(nullptr), myWindow(nullptr),
myWindowWidth(1600), myWindowHeight(900), 
myRenderWidth(myWindowWidth), myRenderHeight(myWindowHeight)
{
}

DragonEngine::Engine::~Engine()
{
	Shutdown();
}

int DragonEngine::Engine::Start()
{
	SDL_SetAppMetadata("Example Renderer Clear", "1.0", "com.example.renderer-clear");

	TTF_Init();

	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	if (!SDL_CreateWindowAndRenderer("DragonEngine", myWindowWidth, myWindowHeight, SDL_WINDOW_RESIZABLE, &myWindow, &myRenderer))
	{
		SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}
	SDL_SetRenderLogicalPresentation(myRenderer, myRenderWidth, myRenderHeight, SDL_LOGICAL_PRESENTATION_LETTERBOX);

	DragonEngine::Debug::Initialize();

	return SDL_APP_CONTINUE;  /* carry on with the program! */
}

void DragonEngine::Engine::Shutdown()
{
	/* SDL will clean up the window/renderer for us. */
	if (myRenderer) { SDL_DestroyRenderer(myRenderer); myRenderer = NULL; }
	if (myWindow) { SDL_DestroyWindow(myWindow);  myWindow = NULL; }
	TTF_Quit();
	SDL_Quit();
}

void DragonEngine::Engine::StartRender()
{
	/* choose the color for the frame we will draw. */
	const float color = 20.f / 255.f;
	SDL_SetRenderDrawColorFloat(myRenderer, color, color, color, SDL_ALPHA_OPAQUE_FLOAT);  /* new color, full alpha. */
	/* clear the window to the draw color. */
	SDL_RenderClear(myRenderer);
}

void DragonEngine::Engine::RenderPresent()
{
	/* show the new frame. */
	SDL_RenderPresent(myRenderer);
}
