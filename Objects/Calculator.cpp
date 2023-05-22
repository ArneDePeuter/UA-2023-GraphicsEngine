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


void Calculator::findBounds(const Vector3D &P, const Vector3D &Q, const double &y, double& xL, double& xR, bool &foundL, bool &foundR) {
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
    Vector3D normaalVector = Calculator::calcNormal(A,B,C);

    double k = Vector3D::dot(normaalVector, A);

    dzdx = normaalVector.x/(-d*k);
    dzdy = normaalVector.y/(-d*k);
}

void Calculator::fill_zbuf_triag(ZBuffer &buffer, const Triangle &t, const double &d, const double &dx, const double &dy) {
    Vector3D A = t.A;
    Vector3D B = t.B;
    Vector3D C = t.C;

    Vector3D newA = Vector3D::point(((d*A.x)/-A.z)+dx, ((d*A.y)/-A.z)+dy, A.z);
    Vector3D newB = Vector3D::point(((d*B.x)/-B.z)+dx, ((d*B.y)/-B.z)+dy, B.z);
    Vector3D newC = Vector3D::point(((d*C.x)/-C.z)+dx, ((d*C.y)/-C.z)+dy, C.z);

    std::vector<double> yVals = {newA.y, newB.y, newC.y};
    int yMin = lround(*std::min_element(yVals.begin(), yVals.end())), yMax = lround(*std::max_element(yVals.begin(), yVals.end()));

    double xG = (newA.x+newB.x+newC.x)/3;
    double yG = (newA.y+newB.y+newC.y)/3;
    double oneOverzG = (1/(3*newA.z)) + (1/(3*newB.z)) + (1/(3*newC.z));

    double dzdx, dzdy;
    calculateDZs(newA, newB, newC, d, dzdx, dzdy);
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
        int xRint = lround(xR+0.5);
        for (int x = xLint; x <= xRint; x++) {
            double bufVal  = 1.0001*oneOverzG + (x-xG)*dzdx + (y-yG)*dzdy;
            buffer.apply(x,y,bufVal);
        }
    }
}

void Calculator::findBounds(const std::vector<Triangle> &triangles, double &xMin, double &xMax, double &yMin, double &yMax) {
    for (const Triangle &t:triangles) {
        std::vector<double> xvals = {t.A.x, t.B.x, t.C.x};
        std::vector<double> yvals = {t.A.y, t.B.y, t.C.y};

        double minX = *std::min_element(xvals.begin(), xvals.end());
        double maxX = *std::max_element(xvals.begin(), xvals.end());
        double minY = *std::min_element(yvals.begin(), yvals.end());
        double maxY = *std::max_element(yvals.begin(), yvals.end());

        xMin = std::min(xMin, minX);
        xMax = std::max(xMax, maxX);
        yMin = std::min(yMin, minY);
        yMax = std::max(yMax, maxY);
    }
}
