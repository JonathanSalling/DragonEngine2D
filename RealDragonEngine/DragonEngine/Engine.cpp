#include "Engine.h"
#include <SDL3/SDL_render.h>
#include "SDL3/SDL_log.h"
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_mixer/SDL_mixer.h>
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
	if (SDL_Init(SDL_INIT_VIDEO) == false)
	{
		SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	if (TTF_Init() == false)
	{
		SDL_Log("Couldn't initialize SDL_TTF: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	if (!MIX_Init()) 
	{
		SDL_Log("Couldn't init SDL_mixer library: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	myMixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);
	if (!myMixer) 
	{
		SDL_Log("Couldn't create mixer on default device: %s", SDL_GetError());
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
	if (myMixer)
	{
		MIX_DestroyMixer(myMixer);
		myMixer = nullptr;
	}
	MIX_Quit();

	TTF_Quit();

	/* SDL will clean up the window/renderer for us. */
	if (myRenderer) { SDL_DestroyRenderer(myRenderer); myRenderer = NULL; }
	if (myWindow) { SDL_DestroyWindow(myWindow);  myWindow = NULL; }
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
