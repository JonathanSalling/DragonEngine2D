#pragma once
#include <variant>
#include <vector>
#include "Color.h"
#include "Vector.h"

struct SDL_Renderer;

namespace DragonEngine
{
	class Debug
	{
	public:
		inline static DragonEngine::Color myDrawColor = DragonEngine::Color::Red;

	private:
		struct Data
		{
			double myDrawUntil;

			struct Box { float x, y, w, h; };
			struct Line { float x0, y0, x1, y1; };
			struct Circle { DragonEngine::Vector2f center; float radius; };
			struct Point { float x, y; };

			std::variant<Box, Line, Circle, Point> myShape;

			template <typename Shape>
			Data(const double aDuration, Shape&& aShape) : myDrawUntil(aDuration), myShape(aShape) {}

			//Data(double aDuration, Box aBox) : myDrawUntil(aDuration), myShape(aBox) {}
			//Data(double aDuration, Line aLine) : myDrawUntil(aDuration), myShape(aLine) {}
			//Data(double aDuration, Circle aCircle) : myDrawUntil(aDuration), myShape(aCircle) {}
			//Data(double aDuration, Point aPoint) : myDrawUntil(aDuration), myShape(aPoint) {}
		};

#ifndef NDEBUG
	public:
		static void Initialize();
		static void Render(SDL_Renderer* aRenderer) { myInstance->RenderInternal(aRenderer); }

		// Debug build; methods implemented
		static void DrawPoint(DragonEngine::Vector2f aPosition, float aStayForSeconds = -1.0f);
		static void DrawBox(DragonEngine::Vector2f aPosition, DragonEngine::Vector2f aSize, float aStayForSeconds = -1.0f);
		//static void DrawBox2(DragonUtilities::Vector2f first, DragonUtilities::Vector2f second, float aStayForSeconds = 0.0f);
		static void DrawLine(DragonEngine::Vector2f aStart, DragonEngine::Vector2f aEnd, float aStayForSeconds = -1.0f);
		static void DrawCircle(DragonEngine::Vector2f aCenter, float aRadius, float aStayForSeconds = -1.0f);

		void RenderInternal(SDL_Renderer* aRenderer);

		static void RenderElement(Data::Point aPoint, SDL_Renderer* aRenderer);
		static void RenderElement(Data::Box aBox, SDL_Renderer* aRenderer);
		static void RenderElement(Data::Line aLine, SDL_Renderer* aRenderer);
		static void RenderElement(Data::Circle aCircle, SDL_Renderer* aRenderer);
#else
	public:
		// Release build; empty methods
		static void Initialize() noexcept {}
		static void Render(SDL_Renderer* aRenderer) noexcept { aRenderer; }

		static void DrawPoint(DragonEngine::Vector2f aVector, float aStayForSeconds = 0.0f) noexcept { aVector; aStayForSeconds; }
		static void DrawBox(DragonEngine::Vector2f aPosition, DragonEngine::Vector2f aSize, float aStayForSeconds = 0.0f) noexcept { aPosition; aSize; aStayForSeconds; }
		static void DrawLine(DragonEngine::Vector2f aStart, DragonEngine::Vector2f aEnd, float aStayForSeconds = 0.0f) noexcept { aStart; aEnd; aStayForSeconds; }
		static void DrawCircle(DragonEngine::Vector2f aCenter, float aRadius, float aStayForSeconds = -1.0f) noexcept { aCenter; aRadius; aStayForSeconds; }
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


