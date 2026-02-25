#pragma once
#include <SDL3/SDL_init.h>

struct SDL_Renderer;

namespace DragonEngine
{
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

		SDL_Renderer* GetRenderer() const { return myRenderer; }
		SDL_Window* GetWindow() const { return myWindow; }

		unsigned short GetWindowWidth() const { return myWindowWidth; }
		unsigned short GetWindowHeight() const { return myWindowHeight; }

		const unsigned short GetRenderWidth() const { return myRenderWidth; }
		const unsigned short GetRenderHeight() const { return myRenderHeight; }

	private:
		/* We will use this renderer to draw into this window every frame. */
		SDL_Renderer* myRenderer;
		SDL_Window* myWindow;

		/* How big should the window be? */
		unsigned short myWindowWidth;
		unsigned short myWindowHeight;

		/* What resolution should we render everything in?*/
		unsigned short myRenderWidth;
		unsigned short myRenderHeight;
	};
}

