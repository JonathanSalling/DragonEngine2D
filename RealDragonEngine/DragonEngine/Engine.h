#pragma once
#include <SDL3/SDL_init.h>

struct SDL_Renderer;

class Engine
{
public:
	Engine();
	~Engine();
	SDL_AppResult Start();
	void Shutdown();

	static Engine& GetInstance()
	{
		static Engine instance;
		return instance;
	}

	/* We will use this renderer to draw into this window every frame. */
	SDL_Renderer* myRenderer;
	SDL_Window* myWindow;
};

