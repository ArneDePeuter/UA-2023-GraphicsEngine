#ifndef ENGINE_RENDERER_H
#define ENGINE_RENDERER_H

#include "../Include/easy_image.h"
#include "Line2D.h"
#include "Triangle.h"
#include "Light.h"

class Scene;

class Renderer {
public:
    static img::EasyImage draw2DLines(const img::Color &backgroundcolor, std::list<Line2D> lines, const int &size, const bool &zbuf);
    static img::EasyImage drawZBufTriangles(const Scene &s, const img::Color &backgroundcolor, const int &size);
};


#endif //ENGINE_RENDERER_H
