#include <fstream>
#include "Light.h"
#include "Line2D.h"
#include "Scene.h"
#include "Renderer.h"

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
    Vector3D pixelLight = pixelEye;
    pixelLight *= inverseEye;
    pixelLight *= lightEye;

    int plx = lround(((pixelLight.x*d)/-pixelLight.z)+dx);
    int ply = lround(((pixelLight.y*d)/-pixelLight.z)+dy);
    double invZl = 1/pixelLight.z;

    return shadowMask[ply][plx]==invZl;
}

void ShadowPointLight::fillBuffer(const std::vector<Triangle> &triangles) {
    for (const Triangle &triangle:triangles) {
        Calculator::fill_zbuf_triag(shadowMask, triangle, d, dx, dy);
    }
}


void ShadowPointLight::initFully(const std::list<Object3D> &objects) {
    //put objects in normal space coords
    Objects3D normalObjects = objects;
    for (Object3D &obj:normalObjects) {
        obj.applyTransformation(inverseEye);
    }

    //create scene
    ini::DoubleTuple loc = {location.x, location.y, location.z};
    Camera cam = Camera(loc,ClippingSettings(false,{0,0,0},0,0,0,0));
    Scene s = Scene(normalObjects, cam, {}, false);

    //render test
    img::EasyImage img = Renderer::drawZBufTriangles(s, img::Color(125,125,125), 1000);
    std::ofstream f_out("lightTest.bmp",std::ios::trunc | std::ios::out | std::ios::binary);
    f_out << img;

    Lines2D lines = s.project(1);

    //determine offset/scaling values
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

    double imageX = bufferSize * (xRange / std::max(xRange, yRange));
    double imageY = bufferSize * (yRange / std::max(xRange, yRange));

    d = 0.95 * (imageX / xRange);

    Point2D DC(d * ((xMin+xMax)/2), d * ((yMin+yMax)/2));
    dx = imageX / 2 - DC.x, dy = imageY / 2 - DC.y;

    //create buffer
    shadowMask = ZBuffer(lround(imageX),lround(imageY));

    //fill buffer
    fillBuffer(s.getTriangles());
}
