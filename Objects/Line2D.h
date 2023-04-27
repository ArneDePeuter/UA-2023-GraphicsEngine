#ifndef ENGINE_LINE2D_H
#define ENGINE_LINE2D_H

#include "Point2D.h"
#include "../Include/easy_image.h"
#include <list>
#include "ZBuffer.h"
#include <cmath>

class Line2D {
public:
    Line2D(const Point2D &p1, const Point2D &p2, const img::Color &color) : p1(p1), p2(p2), color(color) {}
    Line2D(const Point2D &p1, const Point2D &p2, const double &z1, const double &z2, const img::Color &color) : p1(p1), p2(p2), color(color) {}

    Point2D p1;
    Point2D p2;
    img::Color color;

    void drawBuf(img::EasyImage *surface, ZBuffer &buffer) const {
        surface->draw_zbuf_line(lround(p1.x),
                                lround(p1.y),
                                lround(p2.x),
                                lround(p2.y),
                                lround(p1.z),
                                lround(p2.z), color, buffer);
    }
    void draw(img::EasyImage *surface) const {
        surface->draw_line(lround(p1.x),
                           lround(p1.y),
                           lround(p2.x),
                           lround(p2.y), color);
    }
};

typedef std::list<Line2D> Lines2D;

#endif //ENGINE_LINE2D_H