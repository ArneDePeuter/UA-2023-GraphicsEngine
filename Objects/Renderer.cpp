#include <cmath>
#include "Renderer.h"
#include "Scene.h"
#include "ImageDetails.h"

img::EasyImage
Renderer::draw2DLines(const img::Color &backgroundcolor, std::list<Line2D> lines, const int &size, const bool &zbuf) {
    ImageDetails details = ImageDetails::calculateDetails(lines, size);

    img::EasyImage image(lround(details.imageX), lround(details.imageY), backgroundcolor);

    for (Line2D &l : lines) {
        l.p1.x *= details.d;
        l.p1.y *= details.d;
        l.p2.x *= details.d;
        l.p2.y *= details.d;
    }

    for (Line2D &l : lines) {
        l.p1.x = lround(l.p1.x + details.dx);
        l.p1.y = lround(l.p1.y + details.dy);
        l.p2.x = lround(l.p2.x + details.dx);
        l.p2.y = lround(l.p2.y + details.dy);
    }

    if (zbuf) {
        ZBuffer buffer(lround(details.imageX),lround(details.imageY));
        for (const Line2D& l : lines) {
            l.drawBuf(&image, buffer);
        }
    } else {
        for (const Line2D& l : lines) {
            l.draw(&image);
        }
        return image;
    }
    return image;
}


img::EasyImage Renderer::drawZBufTriangles(const Scene &s, const img::Color &backgroundcolor, const int &size) {
    ImageDetails details = ImageDetails::calculateDetails(s.project(1), size);

    img::EasyImage image(lround(details.imageX), lround(details.imageY), backgroundcolor);

    for (Light *l:s.lights) {
        l->initFully(s.objects3D);
    }

    ZBuffer buffer(lround(details.imageX),lround(details.imageY));
    for (const Triangle &triangle : s.getTriangles()) {
        image.draw_zbuf_triag(buffer, triangle, details.d, details.dx, details.dy, s.lights);
    }
    return image;
}
