#ifndef ENGINE_CALCULATOR_H
#define ENGINE_CALCULATOR_H

#include "../Include/vector3d.h"

class Calculator {
public:
    static double degToRad(double degrees);
    static Matrix scale(const double &scale);
    static Matrix rotate_x(const double &angle);
    static Matrix rotate_y(const double &angle);
    static Matrix rotate_z(const double &angle);
    static Matrix translate(const Vector3D &vector);
    static void calcPolar(const Vector3D &point, double &theta, double &phi, double &r);
    static Matrix superMatrix(const double &s, const int &rx, const int &ry, const int &rz, const Vector3D &move);
    static Matrix eyePointMatrix(const Vector3D &eye);
    static Vector3D rotateVecOnVec(Vector3D &vec, const Vector3D &rotAxis, const double &degAngle);
};


#endif //ENGINE_CALCULATOR_H
