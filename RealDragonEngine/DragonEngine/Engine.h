#pragma once
#include "EngineVector.h"

struct SDL_Renderer;
struct SDL_Window;

namespace DragonEngine
{
	class Engine
	{
	public:
		Engine();
		~Engine();
		int Start();
		void Shutdown();

		void StartRender();
		void RenderPresent();

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

		Vector2f NormalSpaceToScreenSpace(Vector2f const& aNormalizedVector) const 
		{
			return { aNormalizedVector.x * myRenderWidth, aNormalizedVector.y * myRenderHeight };
		}

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

