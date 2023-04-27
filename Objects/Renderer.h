#ifndef ENGINE_RENDERER_H
#define ENGINE_RENDERER_H

#include "../Include/easy_image.h"
#include "Line2D.h"
#include "Triangle.h"
#include "Light.h"

class Renderer {
public:
    static img::EasyImage draw2DLines(const img::Color &backgroundcolor, std::list<Line2D> lines, const int &size, const bool &zbuf);
    static img::EasyImage drawZBufTriangles(const img::Color &backgroundcolor, std::vector<Triangle> triangles, const Lines2D &projectedLines, const int &size,lights3D &lights);
};


#endif //ENGINE_RENDERER_H
