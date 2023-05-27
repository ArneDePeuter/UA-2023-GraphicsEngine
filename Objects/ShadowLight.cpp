#include <fstream>
#include "Light.h"
#include "Line2D.h"
#include "Scene.h"
#include "Renderer.h"
#include "ImageDetails.h"

ShadowPointLight::ShadowPointLight(const ini::DoubleTuple &ambientLight, const ini::DoubleTuple &diffuseLight, const ini::DoubleTuple &specularLight, const Vector3D &location, const int &bufferSize, const Matrix &eye) : SpecularLight(ambientLight, diffuseLight, specularLight, location), bufferSize(bufferSize) {
    inverseEye = Matrix::inv(eye);
    lightEye = Calculator::eyePointMatrix(location);
}

void ShadowPointLight::calculateColor(double &rVal, double &gVal, double &bVal, ini::DoubleTuple ambientReflection, ini::DoubleTuple diffuseReflection, ini::DoubleTuple specularReflection, double reflectionCoeff, Vector3D A, Vector3D B, Vector3D C, Vector3D pixel) const {
    AmbientLight::applyAmbientLight(rVal, gVal, bVal, ambientLight, ambientReflection);
    if (applyLight(pixel)) {
        applyDiffuseLight(rVal, gVal, bVal, diffuseLight, diffuseReflection, pixel, Calculator::calcNormal(A, B, C), location*Matrix::inv(inverseEye), spotAngle);
        applySpecularLight(rVal, gVal, bVal, specularLight, specularReflection, reflectionCoeff, pixel, Calculator::calcNormal(A, B, C), location*Matrix::inv(inverseEye));
    }
}

bool ShadowPointLight::applyLight(const Vector3D &pixel) const {
    Vector3D lightPixel = pixel*inverseEye*lightEye;
    Point2D projectedPixel = Calculator::projectPoint(lightPixel, d, dx, dy);

    double ax = projectedPixel.x - std::floor(projectedPixel.x);
    double ay = projectedPixel.y - std::floor(projectedPixel.y);

    Point2D A = projectedPixel;
    A.x -= ax; A.y += (1-ay);

    Point2D B = projectedPixel;
    B.x += (1-ax); B.y += (1-ay);

    Point2D C = projectedPixel;
    C.x -= ax; C.y -= ay;

    Point2D D = projectedPixel;
    D.x += (1-ax); D.y -= ay;

    double invZA = shadowMask[lround(A.y)][lround(A.x)];
    double invZB = shadowMask[lround(B.y)][lround(B.x)];
    double invZC = shadowMask[lround(C.y)][lround(C.x)];
    double invZD = shadowMask[lround(D.y)][lround(D.x)];

    double invZE = (1-ax)*invZA + ax*invZB;
    double invZF = (1-ax)*invZC + ax*invZD;

    double invZl = ay*invZE + (1-ay)*invZF;

    return (std::abs(1/lightPixel.z - invZl) < 1e-5);
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

    //determine offset/scaling values
    Lines2D lines = s.project(1);
    ImageDetails details = ImageDetails::calculateDetails(s.project(1), bufferSize);
    d = details.d; dx = details.dx; dy = details.dy;

    //create buffer
    shadowMask = ZBuffer(lround(details.imageX),lround(details.imageY));

    //fill buffer
    fillBuffer(s.getTriangles());
}
