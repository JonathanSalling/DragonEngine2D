#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>

/* We will use this renderer to draw into this window every frame. */
static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
static SDL_Texture* texture = NULL;

static float playerX = 320.0f;
static float playerY = 240.0f;
static float playerW = 32.0f;
static float playerH = 32.0f;
static float speed = 200.0f; /* pixels/sec */

static bool leftDown = false;
static bool rightDown = false;
static bool upDown = false;
static bool downDown = false;

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

	if (!SDL_CreateWindowAndRenderer("DragonEngine", 640, 480, SDL_WINDOW_RESIZABLE, &window, &renderer))
	{
		SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}
	SDL_SetRenderLogicalPresentation(renderer, 640, 480, SDL_LOGICAL_PRESENTATION_LETTERBOX);

	/* Load a image */
	texture = IMG_LoadTexture(renderer, "vayne.png");
	if (!texture)
	{
		SDL_Log("Couldn't load icon: %s\n", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
	appstate;  /* avoid unused parameter warning */

	switch (event->type)
	{
	case SDL_EVENT_KEY_DOWN:
		switch (event->key.scancode)
		{
		case SDL_SCANCODE_LEFT:  leftDown = true; break;
		case SDL_SCANCODE_RIGHT: rightDown = true; break;
		case SDL_SCANCODE_UP:    upDown = true; break;
		case SDL_SCANCODE_DOWN:  downDown = true; break;
		default: break;
		}
		break;

	case SDL_EVENT_KEY_UP:
		switch (event->key.scancode)
		{
		case SDL_SCANCODE_LEFT:  leftDown = false; break;
		case SDL_SCANCODE_RIGHT: rightDown = false; break;
		case SDL_SCANCODE_UP:    upDown = false; break;
		case SDL_SCANCODE_DOWN:  downDown = false; break;
		default: break;
		}
		break;
	}

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

	/* time */
	static uint64_t lastTicks = 0;
	uint64_t ticks = SDL_GetTicks();
	float DeltaTime = 0.016f;
	if (lastTicks != 0) DeltaTime = (ticks - lastTicks) / 1000.0f;
	lastTicks = ticks;

	/* move player using key state */
	float VelocityX = 0.0f, VelocityY = 0.0f;
	if (leftDown)  VelocityX -= 1.0f;
	if (rightDown) VelocityX += 1.0f;
	if (upDown)    VelocityY -= 1.0f;
	if (downDown)  VelocityY += 1.0f;

	/* normalize diagonal movement (optional) */
	if (VelocityX != 0.0f || VelocityY != 0.0f) 
	{
		float invlen = 1.0f / SDL_sqrtf(VelocityX * VelocityX + VelocityY * VelocityY);
		VelocityX *= invlen;
		VelocityY *= invlen;
	}

	playerX += VelocityX * speed * DeltaTime;
	playerY += VelocityY * speed * DeltaTime;

	int w = 0, h = 0;
	SDL_FRect dst;
	const float scale = 1.0f;

	/* Center the icon and scale it up */
	SDL_GetRenderOutputSize(renderer, &w, &h);
	//SDL_SetRenderScale(renderer, scale, scale);
	SDL_GetTextureSize(texture, &dst.w, &dst.h);
	dst.x = ((w / scale) - dst.w) / 2;
	dst.y = ((h / scale) - dst.h) / 2;


	const double now = ((double)SDL_GetTicks()) / 1000.0;  /* convert from milliseconds to seconds. */
	/* choose the color for the frame we will draw. The sine wave trick makes it fade between colors smoothly. */
	const float red = (float)(0.5 + 0.5 * SDL_sin(now));
	const float green = (float)(0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 2 / 3));
	const float blue = (float)(0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 4 / 3));
	SDL_SetRenderDrawColorFloat(renderer, red, green, blue, SDL_ALPHA_OPAQUE_FLOAT);  /* new color, full alpha. */

	/* clear the window to the draw color. */
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColorFloat(renderer, 1.0f, 1.0f, 1.0f, SDL_ALPHA_OPAQUE_FLOAT);

	SDL_FRect playerRect = { playerX - playerW * 0.5f, playerY - playerH * 0.5f,playerW,playerH };
	SDL_RenderFillRect(renderer, &playerRect);

	SDL_RenderTexture(renderer, texture, NULL, &dst);

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