#ifndef ENGINE_CALCULATOR_H
#define ENGINE_CALCULATOR_H

#include "../Include/vector3d.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include "ZBuffer.h"
#include "Triangle.h"
#include "Point2D.h"

class Calculator {
public:
    static double degToRad(double degrees);

    static Matrix scale(const double &scale);

    static Matrix rotate_x(const double &angle);

    static Matrix rotate_y(const double &angle);

    static Matrix rotate_z(const double &angle);

    static Matrix translate(const Vector3D &vector);

    static Matrix superMatrix(const double &s, const int &rx, const int &ry, const int &rz, const Vector3D &move);

    static Matrix eyePointMatrix(const double &theta, const double &phi, const double &r);

    static Matrix eyePointMatrix(const Vector3D &eye);

    static void calcPolar(const Vector3D &point, double &theta, double &phi, double &r);

    static Vector3D calcNormal(const Vector3D &A, const Vector3D &B, const Vector3D &C);

    static void calculateDZs(const Vector3D &A, const Vector3D &B, const Vector3D &C, const double &d, double &dzdx, double &dzdy);

    static void findBounds(const Point2D &P, const Point2D &Q, const double &y, double &xL, double &xR, bool &foundL, bool &foundR);

    static void fill_zbuf_triag(ZBuffer &buffer, const Triangle &t, const double &d, const double &dx, const double &dy);

    static Point2D projectPoint(const Vector3D &point, const double &d, const double &dx, const double &dy);
};

#endif //ENGINE_CALCULATOR_H
