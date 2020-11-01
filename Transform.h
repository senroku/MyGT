#pragma once

#include "Vec2.h"
#include <utility>

namespace MyGT {
    struct Transform
    {
        Transform() = default;

        constexpr Transform(Vec2 _position)
            :position(_position),
            parent(nullptr) {}

        constexpr Transform(Transform* _parent)
            : position(),
            parent(_parent) {}

        constexpr Transform(Vec2 _position, Transform* _parent)
            : position(_position),
            parent(_parent) {}

        ~Transform() {}


        constexpr Vec2 get_world_position()
        {

            return parent->get_world_position();
        }

    public:
        Vec2 position;
        //���S���l����sharedptr���g���ׂ��ł�.
        Transform* parent;
    };
}