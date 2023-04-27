#include "Calculator.h"
#define _USE_MATH_DEFINES
#include <cmath>

double Calculator::degToRad(double degrees) {
    return degrees * M_PI / 180;
}

Matrix Calculator::scale(const double &scale) {
    Matrix m;
    m(1,1) = scale;
    m(2,2) = scale;
    m(3,3) = scale;
    return m;
}

Matrix Calculator::rotate_x(const double &angle) {
    Matrix m;
    double radians_angle = degToRad(angle);
    m(2,2) = cos(radians_angle);
    m(2,3) = sin(radians_angle);
    m(3,2) = -sin(radians_angle);
    m(3,3) = cos(radians_angle);
    return m;
}

Matrix Calculator::rotate_y(const double &angle) {
    Matrix m;
    double radians_angle = degToRad(angle);
    m(1,1) = cos(radians_angle);
    m(1,3) = -sin(radians_angle);
    m(3,1) = sin(radians_angle);
    m(3,3) = cos(radians_angle);
    return m;
}

Matrix Calculator::rotate_z(const double &angle) {
    Matrix m;
    double radians_angle = degToRad(angle);
    m(1,1) = cos(radians_angle);
    m(1,2) = sin(radians_angle);
    m(2,1) = -sin(radians_angle);
    m(2,2) = cos(radians_angle);
    return m;
}

Matrix Calculator::translate(const Vector3D &vector) {
    Matrix m;
    m(4,1) = vector.x;
    m(4,2) = vector.y;
    m(4,3) = vector.z;
    return m;
}

Matrix Calculator::superMatrix(const double &s, const int &rx, const int &ry, const int &rz, const Vector3D &move) {
    return scale(s) * rotate_x(rx) * rotate_y(ry) * rotate_z(rz) * translate(move);
}

Matrix Calculator::eyePointMatrix(const double &theta, const double &phi, const double &r) {
    Matrix m;
    m(1,1) = -sin(theta);
    m(1,2) = -cos(theta)*cos(phi);
    m(1,3) = cos(theta)*sin(phi);
    m(2,1) = cos(theta);
    m(2,2) = -sin(theta)*cos(phi);
    m(2,3) = sin(theta)*sin(phi);
    m(3,2) = sin(phi);
    m(3,3) = cos(phi);
    m(4,3) = -r;
    return m;
}

void Calculator::calcPolar(const Vector3D &point, double &theta, double &phi, double &r) {
    double x = point.x, y = point.y, z = point.z;
    r = sqrt(pow(x,2)+pow(y,2)+pow(z,2));
    theta = std::atan2(y,x);
    phi = std::acos(z/r);
}

Matrix Calculator::eyePointMatrix(const Vector3D &eye) {
    Matrix m;
    double theta, phi, r;
    calcPolar(eye, theta, phi, r);
    m(1,1) = -sin(theta);
    m(1,2) = -cos(theta)*cos(phi);
    m(1,3) = cos(theta)*sin(phi);
    m(2,1) = cos(theta);
    m(2,2) = -sin(theta)*cos(phi);
    m(2,3) = sin(theta)*sin(phi);
    m(3,2) = sin(phi);
    m(3,3) = cos(phi);
    m(4,3) = -r;
    return m;
}