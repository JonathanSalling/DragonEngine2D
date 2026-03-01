#pragma once
#include <variant>
#include <vector>
#include "Color.h"
#include "EngineVector.h"

struct SDL_Renderer;

namespace DragonEngine
{
	class Debug
	{
	public:
		inline static DragonEngine::Color myDrawColor = DragonEngine::Color::Red;

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
		struct Data 
		{
			double myDrawUntil;

			struct Box { float x, y, w, h; };
			struct Line { float x0, y0, x1, y1; };
			struct Circle { DragonEngine::Vector2f myCenter; float myRadius; };
			struct Point { float x, y; };

			std::variant<Box, Line, Circle, Point> myShape;

			template <typename Shape>
			Data(double aDuration, Shape&& aShape) : myDrawUntil(aDuration), myShape(aShape) {}

			//Data(double aDuration, Box aBox) : myDrawUntil(aDuration), myShape(aBox) {}
			//Data(double aDuration, Line aLine) : myDrawUntil(aDuration), myShape(aLine) {}
			//Data(double aDuration, Circle aCircle) : myDrawUntil(aDuration), myShape(aCircle) {}
			//Data(double aDuration, Point aPoint) : myDrawUntil(aDuration), myShape(aPoint) {}
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


