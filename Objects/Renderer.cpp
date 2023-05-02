#include <cmath>
#include "Renderer.h"
#include <limits>

img::EasyImage
Renderer::draw2DLines(const img::Color &backgroundcolor, std::list<Line2D> lines, const int &size, const bool &zbuf) {
    //1. Determine xmin, xmax, ymin, ymax
    double xMin = std::numeric_limits<double>::max(), xMax = std::numeric_limits<double>::min(), yMin = std::numeric_limits<double>::max(), yMax = std::numeric_limits<double>::min();
    for (const Line2D& l : lines) {
        double lMinX = std::min(l.p1.x, l.p2.x), lMaxX = std::max(l.p1.x, l.p2.x);
        double lMinY = std::min(l.p1.y, l.p2.y), lMaxY = std::max(l.p1.y, l.p2.y);
        xMin = std::min(xMin, lMinX);
        xMax = std::max(xMax, lMaxX);
        yMin = std::min(yMin, lMinY);
        yMax = std::max(yMax, lMaxY);
    }
    double xRange = xMax - xMin, yRange = yMax - yMin;
    //2. Calculate size of image
    double imageX = size * (xRange / std::max(xRange, yRange));
    double imageY = size * (yRange / std::max(xRange, yRange));
    img::EasyImage image(lround(imageX), lround(imageY), backgroundcolor);

    //3. Scale
    double d = 0.95 * (imageX / xRange);
    for (Line2D &l : lines) {
        l.p1.x *= d;
        l.p1.y *= d;
        l.p2.x *= d;
        l.p2.y *= d;
    }

    //4 and 5. Move
    Point2D DC(d * ((xMin+xMax)/2), d * ((yMin+yMax)/2));
    double dx = imageX / 2 - DC.x, dy = imageY / 2 - DC.y;
    for (Line2D &l : lines) {
        l.p1.x = lround(l.p1.x + dx);
        l.p1.y = lround(l.p1.y + dy);
        l.p2.x = lround(l.p2.x + dx);
        l.p2.y = lround(l.p2.y + dy);
    }

    //6. draw
    if (zbuf) {
        ZBuffer buffer(lround(imageX),lround(imageY));
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

img::EasyImage
Renderer::drawZBufTriangles(const img::Color &backgroundcolor, std::vector<Triangle> triangles, const Lines2D &projectedLines, const int &size, lights3D &lights) {
    double xMin = std::numeric_limits<double>::max(), xMax = std::numeric_limits<double>::min(), yMin = std::numeric_limits<double>::max(), yMax = std::numeric_limits<double>::min();
    for (const Line2D& l : projectedLines) {
        double lMinX = std::min(l.p1.x, l.p2.x), lMaxX = std::max(l.p1.x, l.p2.x);
        double lMinY = std::min(l.p1.y, l.p2.y), lMaxY = std::max(l.p1.y, l.p2.y);
        xMin = std::min(xMin, lMinX);
        xMax = std::max(xMax, lMaxX);
        yMin = std::min(yMin, lMinY);
        yMax = std::max(yMax, lMaxY);
    }
    double xRange = xMax - xMin, yRange = yMax - yMin;

    double imageX = size * (xRange / std::max(xRange, yRange));
    double imageY = size * (yRange / std::max(xRange, yRange));
    img::EasyImage image(lround(imageX), lround(imageY), backgroundcolor);

    double d = 0.95 * (imageX / xRange);

    Point2D DC(d * ((xMin+xMax)/2), d * ((yMin+yMax)/2));
    double dx = imageX / 2 - DC.x, dy = imageY / 2 - DC.y;

    ZBuffer buffer(lround(imageX),lround(imageY));
    for (const Triangle &triangle : triangles) {
        image.draw_zbuf_triag(buffer, triangle.A, triangle.B, triangle.C, d, dx, dy,
                              triangle.ambientReflection, triangle.diffuseReflection, triangle.specularReflection, triangle.reflectionCoefficient, lights);
    }
    return image;
}
