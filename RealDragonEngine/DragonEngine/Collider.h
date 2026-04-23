#pragma once
//#include "BoxCollider.hpp"
//#include "Sphere.hpp"

namespace DragonEngine
{
    class BoxCollider;
    class SphereCollider;
}

namespace DragonEngine
{
    enum class ColliderType
    {
        Box,
        Sphere
    };

    class Collider
    {
    public:
        virtual ~Collider() = default;

        virtual ColliderType GetType() const = 0;
        virtual bool Intersects(const Collider& other) const;
        virtual bool Intersects(const BoxCollider& other) const;
        virtual bool Intersects(const SphereCollider& other) const;
    };
}

