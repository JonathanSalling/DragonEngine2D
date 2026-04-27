#pragma once
#include "Plane.hpp"
#include "Ray.hpp"
#include "BoxCollider.hpp"
#include "SphereCollider.hpp"

namespace DragonEngine
{
	template<typename T>
	bool IntersectionPlaneRay(const Plane<T>& aPlane, const Ray<T>& aRay, Vector3<T>& aOutIntersectionPoint);

	template<typename T>
	bool IntersectionAABBRay(const BoxCollider& aAABB, const Ray<T>& aRay);

	template<typename T>
	bool IntersectionSphereRay(const SphereCollider& aSphere, const Ray<T>& aRay);
	template<typename T>
	bool IntersectionPlaneRay(const Plane<T>& aPlane, const Ray<T>& aRay, Vector3<T>& aOutIntersectionPoint)
	{
		T denom = aPlane.GetNormal().Dot(aRay.GetDirection());

		if (abs(denom) > 0.0001f)
		{
			T t = (aPlane.GetPoint() - aRay.GetOrigin()).Dot(aPlane.GetNormal()) / denom;
			if (t >= 0)
			{
				return true;
			}
		}
		return false;
	}

	template<typename T>
	bool IntersectionAABBRay(const BoxCollider& aAABB, const Ray<T>& aRay)
	{
		if (aAABB.IsInside(aRay.GetOrigin()))
		{
			return true;
		}
		return false;
	}

	template<typename T>
	bool IntersectionSphereRay(const SphereCollider& aSphere, const Ray<T>& aRay)
	{
		
		Ray<T> origi = aRay;
		Vector3<T> originToSphere = aSphere.GetCenter() - aRay.GetOrigin();
		Vector3<T> hej = aRay.GetDirection();
		T dotDir = originToSphere.Dot(aRay.GetDirection());

		if (dotDir <= 0.0f)
		{
			return false;
		}

		Vector3<T> closestToSphere = aRay.GetDirection() * dotDir;

		return (originToSphere.LengthSqr() - closestToSphere.LengthSqr()) <= (aSphere.GetRadius() * aSphere.GetRadius());

		return true;
	}
}