#ifndef ENGINE_POINT2D_H
#define ENGINE_POINT2D_H

class Point2D {
public:
    Point2D(const double &x, const double &y) : x(x), y(y), z(0) {}
    Point2D(const double &x, const double &y, const double &z) : x(x), y(y), z(z) {}

    double x;
    double y;
    double z;
};


#endif //ENGINE_POINT2D_H
