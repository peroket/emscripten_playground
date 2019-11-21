#pragma once

#include "math/Rectangle.hpp"
#include "render/Color.hpp"

namespace Engine
{
// Class serving as base for rendering
// At least for now, the only thing the engine renders is rectangles
class RenderObject
{
public:
    // The depth does not change the size, just the order of render with other objects
    RenderObject(Math::Rectangle const & position,
                 Math::Float             depth = 0.0,
                 Render::Color const &   color = {1.0}) noexcept;

    void render() const;

private:
    Math::Rectangle m_position;
    Render::Color   m_color;
    Math::Float     m_depth;
};
}