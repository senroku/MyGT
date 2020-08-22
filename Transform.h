#pragma once

#include "Vec2.h"
#include <utility>

struct Transform 
{
    Transform() = default;

    constexpr Transform(Vec2 _position)
        :position(_position),
        parent(nullptr) {}

    constexpr Transform(Transform* _parent)
        : position(),
        parent(_parent) {}

    constexpr Transform(Vec2 _position,Transform* _parent)
        : position(_position),
        parent(_parent) {}

    ~Transform() {}


    constexpr Vec2 getWorldPosition() 
    {

        return parent->getWorldPosition();
    }

public:
    Vec2 position;
    //ˆÀ‘S«l—¶‚Åsharedptr‚ğg‚¤‚×‚«‚Å‚Í.
    Transform* parent;
};