#include <algorithm>
#include "Calculator.h"


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

Vector3D Calculator::calcNormal(const Vector3D &A, const Vector3D &B, const Vector3D &C) {
    return Vector3D::normalise(Vector3D::cross(B - A, C - A));
}


void Calculator::findBounds(const Point2D &P, const Point2D &Q, const double &y, double &xL, double &xR, bool &foundL, bool &foundR) {
    if ((y < P.y && y < Q.y) || (y > P.y && y > Q.y)) { return; }
    if (P.x == Q.x) {return;}

    double slope = (P.x - Q.x) / (P.y - Q.y);
    double x = Q.x + slope * (y - Q.y);

    if (x < xL) {
        foundL = true;
        xL = x;
    }
    if (x > xR) {
        foundR = true;
        xR = x;
    }
}

void Calculator::calculateDZs(const Vector3D &A, const Vector3D &B, const Vector3D &C, const double &d, double &dzdx, double &dzdy) {
    Vector3D w = Vector3D::cross(B - A, C - A);

    double k = Vector3D::dot(w, A);

    dzdx = w.x/(-d*k);
    dzdy = w.y/(-d*k);
}

void Calculator::fill_zbuf_triag(ZBuffer &buffer, const Triangle &t, const double &d, const double &dx, const double &dy) {
    Vector3D A = t.A;
    Vector3D B = t.B;
    Vector3D C = t.C;

    Point2D newA = Calculator::projectPoint(A,d, dx, dy);
    Point2D newB = Calculator::projectPoint(B,d, dx, dy);
    Point2D newC = Calculator::projectPoint(C,d, dx, dy);

    std::vector<double> yVals = {newA.y, newB.y, newC.y};
    double yMind = *std::min_element(yVals.begin(), yVals.end()), yMaxd = *std::max_element(yVals.begin(), yVals.end());
    int yMin = lround(yMind+0.5), yMax = lround(yMaxd-0.5);

    double xG = (newA.x+newB.x+newC.x)/3;
    double yG = (newA.y+newB.y+newC.y)/3;
    double oneOverzG = (1/(3*newA.z)) + (1/(3*newB.z)) + (1/(3*newC.z));

    double dzdx, dzdy;
    calculateDZs(A, B, C, d, dzdx, dzdy);
    double xL, xR;
    for (int y = yMin; y <= yMax; y++) {
        xL = std::numeric_limits<double>::infinity();
        xR = -std::numeric_limits<double>::infinity();

        bool foundR = false, foundL = false;
        findBounds(newA, newB, y, xL, xR, foundL, foundR);
        findBounds(newA, newC, y, xL, xR, foundL, foundR);
        findBounds(newB, newC, y, xL, xR, foundL, foundR);
        if (!foundL || !foundR) continue;

        int xLint = lround(xL+0.5);
        int xRint = lround(xR-0.5);
        for (int x = xLint; x <= xRint; x++) {
            double bufVal  = oneOverzG + (x-xG)*dzdx + (y-yG)*dzdy;
            buffer.apply(x,y,bufVal);
        }
    }
}

Point2D Calculator::projectPoint(const Vector3D &point, const double &d, const double &dx, const double &dy) {
    return {((d*point.x)/-point.z)+dx, ((d*point.y)/-point.z)+dy, point.z};
}
