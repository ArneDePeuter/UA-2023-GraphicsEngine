#include "Light.h"
#include "Line2D.h"

ShadowPointLight::ShadowPointLight(const ini::DoubleTuple &ambientLight, const ini::DoubleTuple &diffuseLight, const ini::DoubleTuple &specularLight, const Vector3D &location, const int &bufferSize, const Matrix &eye) : SpecularLight(ambientLight, diffuseLight, specularLight, location), bufferSize(bufferSize) {
    inverseEye = Matrix::inv(eye);
    lightEye = Calculator::eyePointMatrix(location);
}

void ShadowPointLight::calculateColor(double &rVal, double &gVal, double &bVal, ini::DoubleTuple ambientReflection, ini::DoubleTuple diffuseReflection, ini::DoubleTuple specularReflection, double reflectionCoeff, Vector3D A, Vector3D B, Vector3D C, Vector3D pixel) const {
    AmbientLight::applyAmbientLight(rVal, gVal, bVal, ambientLight, ambientReflection);
    if (applyLight(pixel)) {
        applyDiffuseLight(rVal, gVal, bVal, diffuseLight, diffuseReflection, pixel, Calculator::calcNormal(A, B, C), location, spotAngle);
        applySpecularLight(rVal, gVal, bVal, specularLight, specularReflection, reflectionCoeff, pixel, Calculator::calcNormal(A, B, C), location);
    }
}

bool ShadowPointLight::applyLight(const Vector3D& pixelEye) const {
    Vector3D lightPixel = pixelEye;
    lightPixel *= inverseEye;
    lightPixel *= lightEye;

    int plx = lround(((lightPixel.x*d)/-lightPixel.z) + dx);
    int ply = lround(((lightPixel.y*d)/-lightPixel.z) + dy);
    double invZl = 1/lightPixel.z;

    return shadowMask[ply][plx]==invZl;
}

void ShadowPointLight::fillBuffer(const std::vector<Triangle> &triangles) {
    for (const Triangle &triangle:triangles) {
        Calculator::fill_zbuf_triag(shadowMask, triangle, d, dx, dy);
    }
}

void ShadowPointLight::initFully(const std::vector<Triangle> &triangles) {
    std::vector<Triangle> lightTriangles = triangles;
    //transform to lightCoordinateSystem
    for (Triangle &t : lightTriangles) {
        t.applyMatrix(inverseEye);
        t.applyMatrix(lightEye);
    }

    //init buffer and offset values
    double xMin = std::numeric_limits<double>::max(), xMax = std::numeric_limits<double>::min(), yMin = std::numeric_limits<double>::max(), yMax = std::numeric_limits<double>::min();
    Calculator::findBounds(triangles, xMin, xMax, yMin, yMax);

    double xRange = xMax - xMin, yRange = yMax - yMin;

    double imageX = bufferSize * (xRange / std::max(xRange, yRange));
    double imageY = bufferSize * (yRange / std::max(xRange, yRange));

    d = 0.95 * (imageX / xRange);

    Point2D DC(d * ((xMin+xMax)/2), d * ((yMin+yMax)/2));
    dx = imageX / 2 - DC.x, dy = imageY / 2 - DC.y;

    shadowMask = ZBuffer(lround(imageX),lround(imageY));

    //fill the buffer!
    fillBuffer(lightTriangles);
}

