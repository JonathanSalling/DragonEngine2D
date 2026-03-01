#include "Debug.h"
#include <algorithm>
#include "Timer.hpp"
#include "Engine.h"
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>

void DragonEngine::Debug::Initialize()
{
	if (myInstance) return;

	myInstance = new Debug();

	return;
}

void DragonEngine::Debug::DrawPoint(Vector2f aVector, float aStayForSeconds)
{
	if (!myInstance) return;
	double removeAfterTime = DE::Timer::GetTotalTime() + aStayForSeconds;
	aVector = Engine::GetInstance().NormalSpaceToScreenSpace(aVector);
	myInstance->myElements.emplace_back(Debug::Data({ removeAfterTime, Debug::Data::Point{aVector.x, aVector.y} }));
}

void DragonEngine::Debug::DrawBox(Vector2f aPosition, Vector2f aSize, float aStayForSeconds)
{
	if (!myInstance) return;
	double removeAfterTime = DE::Timer::GetTotalTime() + aStayForSeconds;
	Vector2f screenCoordsPos(Engine::GetInstance().NormalSpaceToScreenSpace(aPosition));
	Vector2f screenCoordsSize(Engine::GetInstance().NormalSpaceToScreenSpace(aSize));


	myInstance->myElements.emplace_back(Debug::Data({ removeAfterTime,
		Debug::Data::Box{screenCoordsPos.x, screenCoordsPos.y, screenCoordsSize.x, screenCoordsSize.y} }));
}

void DragonEngine::Debug::DrawLine(Vector2f aStart, Vector2f aEnd, float aStayForSeconds)
{
	if (!myInstance) return;
	double removeAfterTime = DE::Timer::GetTotalTime() + aStayForSeconds;
	aStart = Engine::GetInstance().NormalSpaceToScreenSpace(aStart);
	aEnd = Engine::GetInstance().NormalSpaceToScreenSpace(aEnd);
	myInstance->myElements.emplace_back(Debug::Data({ removeAfterTime, Debug::Data::Line{aStart.x, aStart.y, aEnd.x, aEnd.y} }));
}

void DragonEngine::Debug::DrawCircle(Vector2f aCenter, float aRadius, float aStayForSeconds)
{
	if (!myInstance) return;
	double removeAfterTime = DE::Timer::GetTotalTime() + aStayForSeconds;
	myInstance->myElements.emplace_back(Debug::Data({
		removeAfterTime,
		Debug::Data::Circle { Engine::GetInstance().NormalSpaceToScreenSpace(aCenter), aRadius}
		}
	));
}

void DragonEngine::Debug::RenderInternal(SDL_Renderer* aRenderer)
{
	SDL_SetRenderDrawColorFloat(Engine::GetInstance().GetRenderer(), myDrawColor.r, myDrawColor.g, myDrawColor.b, myDrawColor.a);
	for (auto& element : myElements)
	{
		std::visit([&](auto& myShape) { RenderElement(myShape, aRenderer); }, element.myShape);
	}

	double time = DE::Timer::GetTotalTime(); //Ooohhh; double time!!
	myElements.erase(std::remove_if(myElements.begin(),
		myElements.end(),
		[time](const Debug::Data& e) { return time > e.myDrawUntil; }),
		myElements.end());
}

void DragonEngine::Debug::RenderElement(Data::Point point, SDL_Renderer* aRenderer)
{
	SDL_RenderPoint(aRenderer, point.x, point.y);
}

void DragonEngine::Debug::RenderElement(Data::Box aBox, SDL_Renderer* aRenderer)
{
	SDL_FRect rect{ aBox.x, aBox.y, aBox.w, aBox.h };
	SDL_RenderRect(aRenderer, &rect);
}

void DragonEngine::Debug::RenderElement(Data::Line line, SDL_Renderer* aRenderer)
{
	SDL_RenderLine(aRenderer, line.x0, line.y0, line.x1, line.y1);
}

void DragonEngine::Debug::RenderElement(Data::Circle aCircle, SDL_Renderer* aRenderer)
{
	constexpr float pi(3.14159265358979f);
	constexpr float resolution(2.5f); //Absolutely overkill for what it is, 1.5f to 3.0f is acceptable to practically perfect circle

	int segments(std::clamp(static_cast<int>(std::ceil(std::sqrt(aCircle.myRadius) * resolution)), 4, 64));
	float radianStep((2 * pi) / segments);
	std::vector<SDL_FPoint> corners;

	for (int i = 0; i < segments + 1; ++i)
	{
		corners.push_back({ aCircle.myCenter.x + std::sin(i * radianStep) * aCircle.myRadius, aCircle.myCenter.y + std::cos(i * radianStep) * aCircle.myRadius });
	}

	SDL_RenderLines(aRenderer, corners.data(), static_cast<int>(corners.size()));
}
