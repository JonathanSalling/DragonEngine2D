#include "Debug.h"
#include <algorithm>
#include "Timer.hpp"
#include "Engine.h"
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>

#ifndef NDEBUG
void DragonEngine::Debug::Initialize()
{
	if (myInstance) return;

	myInstance = new Debug();

	return;
}

void DragonEngine::Debug::DrawPoint(Vector2f aPosition,Color aColor, const float aStayForSeconds)
{
	if (!myInstance) return;
	double removeAfterTime = Timer::GetTotalTime() + aStayForSeconds;
	aPosition = Engine::GetInstance().NormalSpaceToScreenSpace(aPosition);
	myInstance->myElements.emplace_back(Debug::Data({ removeAfterTime, Debug::Data::Point{aPosition.x, aPosition.y}, aColor }));
}

void DragonEngine::Debug::DrawBox(const Vector2f aPosition, const Vector2f aSize,Color aColor, const float aStayForSeconds)
{
	if (!myInstance) return;
	double removeAfterTime = DE::Timer::GetTotalTime() + aStayForSeconds;
	const Vector2f screenCoordsPos(Engine::GetInstance().NormalSpaceToScreenSpace(aPosition));
	const Vector2f screenCoordsSize(Engine::GetInstance().NormalSpaceToScreenSpace(aSize));


	myInstance->myElements.emplace_back(Debug::Data({ removeAfterTime,
		Debug::Data::Box{screenCoordsPos.x, screenCoordsPos.y, screenCoordsSize.x, screenCoordsSize.y}, aColor }));
}

void DragonEngine::Debug::DrawLine(Vector2f aStart, Vector2f aEnd, Color aColor, const float aStayForSeconds)
{
	if (!myInstance) return;
	double removeAfterTime = DE::Timer::GetTotalTime() + aStayForSeconds;
	aStart = Engine::GetInstance().NormalSpaceToScreenSpace(aStart);
	aEnd = Engine::GetInstance().NormalSpaceToScreenSpace(aEnd);
	myInstance->myElements.emplace_back(Debug::Data({ removeAfterTime, Debug::Data::Line{aStart.x, aStart.y, aEnd.x, aEnd.y}, aColor }));
}

void DragonEngine::Debug::DrawCircle(const Vector2f aCenter, const float aRadius, Color aColor, const float aStayForSeconds)
{
	if (!myInstance) return;
	double removeAfterTime = DE::Timer::GetTotalTime() + aStayForSeconds;
	myInstance->myElements.emplace_back(Debug::Data({
		removeAfterTime,
		Debug::Data::Circle { Engine::GetInstance().NormalSpaceToScreenSpace(aCenter), aRadius * Engine::GetInstance().GetRenderHeight()}, aColor
		}
	));
}

void DragonEngine::Debug::RenderInternal(SDL_Renderer* aRenderer)
{
	//SDL_SetRenderDrawColorFloat(Engine::GetInstance().GetRenderer(), myDrawColor.r, myDrawColor.g, myDrawColor.b, myDrawColor.a);
	for (auto& element : myElements)
	{
		SDL_SetRenderDrawColorFloat(aRenderer, element.myColor.r, element.myColor.g, element.myColor.b, element.myColor.a);
		std::visit([&](auto& myShape) { RenderElement(myShape, aRenderer); }, element.myShape);
	}

	double time = Timer::GetTotalTime(); //Ooh; double time!!
	myElements.erase(std::remove_if(myElements.begin(),
		myElements.end(),
		[time](const Debug::Data& e) { return time > e.myDrawUntil; }),
		myElements.end());
}

void DragonEngine::Debug::RenderElement(const Data::Point aPoint, SDL_Renderer* aRenderer)
{
	SDL_RenderPoint(aRenderer, aPoint.x, aPoint.y);
}

void DragonEngine::Debug::RenderElement(const Data::Box aBox, SDL_Renderer* aRenderer)
{
	SDL_FRect rect{ aBox.x, aBox.y, aBox.w, aBox.h };
	SDL_RenderRect(aRenderer, &rect);
}

void DragonEngine::Debug::RenderElement(const Data::Line line, SDL_Renderer* aRenderer)
{
	SDL_RenderLine(aRenderer, line.x0, line.y0, line.x1, line.y1);
}

void DragonEngine::Debug::RenderElement(const Data::Circle aCircle, SDL_Renderer* aRenderer)
{
	constexpr float pi(3.14159265358979f);
	constexpr float resolution(2.5f); //Absolutely overkill for what it is, 1.5f to 3.0f is acceptable to practically perfect circle

	int segments(std::clamp(static_cast<int>(std::ceil(std::sqrt(aCircle.radius) * resolution)), 4, 64));
	float radianStep((2 * pi) / segments);
	std::vector<SDL_FPoint> corners;

	for (int i = 0; i < segments + 1; ++i)
	{
		corners.push_back({ aCircle.center.x + std::sin(i * radianStep) * aCircle.radius, aCircle.center.y + std::cos(i * radianStep) * aCircle.radius });
	}

	SDL_RenderLines(aRenderer, corners.data(), static_cast<int>(corners.size()));
}
#endif
