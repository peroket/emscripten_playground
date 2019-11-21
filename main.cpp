#include <emscripten.h>

#include "engine/RenderObject.hpp"
#include "render/init.hpp"
#include "render/render.hpp"

int main()
{
    Render::initGlAndLoadShaders();
    Engine::RenderObject one({{-0.5, -0.5}, {0.1, 0.5}}, 0.0, {1.0});
    Engine::RenderObject two({{-0.1, -0.7}, {0.5, 0.2}}, 1.0, {0.0, 1.0});
    Engine::RenderObject three({{0.0, -0.2}, {0.6, 0.8}}, -1.0, {0.0, 0.0, 1.0});

    initDraw();
    one.render();
    two.render();
    three.render();
    return 0;
}
