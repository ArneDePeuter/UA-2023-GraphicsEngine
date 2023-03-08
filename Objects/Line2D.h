#ifndef ENGINE_LINE2D_H
#define ENGINE_LINE2D_H

#include "Point2D.h"
#include "../Include/easy_image.h"
#include <list>

class Line2D {
public:
    Line2D() {}
    Line2D(const Point2D &p1, const Point2D &p2, const img::Color &color) : p1(p1), p2(p2), color(color) {}

    Point2D p1;
    Point2D p2;
    img::Color color;

    void draw(img::EasyImage *surface) const {
        surface->draw_line(p1.x, p1.y, p2.x, p2.y, color);
    }
};

typedef std::list<Line2D> Lines2D;

#endif //ENGINE_LINE2D_H