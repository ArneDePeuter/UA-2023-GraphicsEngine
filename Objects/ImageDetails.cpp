#include "ImageDetails.h"

ImageDetails::ImageDetails(double d, double dx, double dy, double imageX, double imageY) : d(d), dx(dx), dy(dy), imageX(imageX), imageY(imageY) {}

ImageDetails ImageDetails::calculateDetails(const Lines2D &lines2D, const int &size) {
    double xMin = std::numeric_limits<double>::max(), xMax = std::numeric_limits<double>::min(), yMin = std::numeric_limits<double>::max(), yMax = std::numeric_limits<double>::min();
    for (const Line2D& l : lines2D) {
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
    double d = 0.95 * (imageX / xRange);

    Point2D DC(d * ((xMin+xMax)/2), d * ((yMin+yMax)/2));
    double dx = imageX / 2 - DC.x, dy = imageY / 2 - DC.y;

    return ImageDetails(d, dx, dy, imageX, imageY);
}