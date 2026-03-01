#pragma once
#include <variant>
#include <vector>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include "Color.h"
#include "EngineVector.h"

namespace DragonEngine {
	class Debug {
	public:
		inline static DragonEngine::Color DrawColor = DragonEngine::Color::Red;

#ifndef NDEBUG
		static void Initialize();
		static void Render(SDL_Renderer* aRenderer) { myInstance->RenderInternal(aRenderer); }

		// Debug build; methods implementated
		static void DrawPoint(DragonEngine::Vector2f aPosition, float aStayForSeconds = -1.0f);
		static void DrawBox(DragonEngine::Vector2f aPosition, DragonEngine::Vector2f aSize, float aStayForSeconds = -1.0f);
		//static void DrawBox2(DragonUtilities::Vector2f first, DragonUtilities::Vector2f second, float aStayForSeconds = 0.0f);
		static void DrawLine(DragonEngine::Vector2f aStart, DragonEngine::Vector2f aEnd, float aStayForSeconds = -1.0f);
		static void DrawCircle(DragonEngine::Vector2f aCenter, float aRadius, float aStayForSeconds = -1.0f);

	private:
		struct Data {
			double drawUntil;

			struct Box { SDL_FRect myRect; };
			struct Line { float x0, y0, x1, y1; };
			struct Circle { DragonEngine::Vector2f myCenter; float myRadius; };
			struct Point { float x, y; };

			std::variant<Box, Line, Circle, Point> shape;
			Data(double du, Box b) : drawUntil(du), shape(b) {}
			Data(double du, Line l) : drawUntil(du), shape(l) {}
			Data(double du, Circle c) : drawUntil(du), shape(c) {}
			Data(double du, Point p) : drawUntil(du), shape(p) {}
		};
		
		void RenderInternal(SDL_Renderer* aRenderer);

		void RenderElement(Data::Point aPoint, SDL_Renderer* aRenderer);
		void RenderElement(Data::Box aBox, SDL_Renderer* aRenderer);
		void RenderElement(Data::Line aLine, SDL_Renderer* aRenderer);
		void RenderElement(Data::Circle aCircle, SDL_Renderer* aRenderer);
#else
		// Release build; empty methods
		static void Initialize(SDL_Renderer* aRenderer) noexcept {}
		static void Render(SDL_Renderer* aRenderer) noexcept {}

		static void DrawPoint(DragonUtilities::Vector2f v, float aStayForSeconds = 0.0f) noexcept {}
		static void DrawBox(DragonUtilities::Vector2f aPosition, DragonUtilities::Vector2f aSize, float aStayForSeconds = 0.0f) noexcept {}
		static void DrawLine(DragonUtilities::Vector2f aStart, DragonUtilities::Vector2f aEnd, float aStayForSeconds = 0.0f) noexcept {}
		static void DrawCircle(DragonUtilities::Vector2f aCenter, float aRadius, float aStayForSeconds = -1.0f) noexcept {}
#endif

	private:
		Debug() {}
		Debug(const Debug&) = delete;
		Debug& operator=(const Debug&) = delete;
		~Debug() {}

		inline static Debug* myInstance = nullptr;

		std::vector<Data> myElements;
	};

}


