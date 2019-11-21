#include "engine/RenderObject.hpp"
#include "render/basic_rectangle.hpp"

namespace Engine
{
RenderObject::RenderObject(Math::Rectangle const & position,
                           Math::Float             depth,
                           Render::Color const &   color) noexcept
    : m_position(position)
    , m_color(color)
    , m_depth(depth)
{
}

void RenderObject::render() const
{
    Render::renderBasicRectangle(m_position.min.x, m_position.min.y, m_position.max.x,
                                 m_position.max.y, m_depth, m_color.r, m_color.b, m_color.g,
                                 m_color.a);
}
}