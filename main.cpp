#include <emscripten.h>

#include "render/init.hpp"
#include "render/render.hpp"

int main()
{
    Render::initGlAndLoadShaders();
    initDraw();
    return 0;
}
