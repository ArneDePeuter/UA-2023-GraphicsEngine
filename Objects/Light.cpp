#include "Light.h"

void AmbientLight::applyAmbientLight(double &rVal, double &gVal, double &bVal, const ini::DoubleTuple &ambientLight, const ini::DoubleTuple &ambientReflection) {
    rVal += ambientReflection[0] * ambientLight[0];
    gVal += ambientReflection[1] * ambientLight[1];
    bVal += ambientReflection[2] * ambientLight[2];
}

void AmbientLight::calculateColor(double &rVal, double &gVal, double &bVal, ini::DoubleTuple ambientReflection, ini::DoubleTuple diffuseReflection, ini::DoubleTuple specularReflection, double reflectionCoeff, Vector3D A, Vector3D B, Vector3D C, Vector3D pixel) const {
    applyAmbientLight(rVal, gVal, bVal, ambientLight, ambientReflection);
}

void AmbientLight::applyTransformation(Matrix m) {}

AmbientLight::AmbientLight(const ini::DoubleTuple &ambientLight) : ambientLight(ambientLight) {}

void InfLight::calculateColor(double &rVal, double &gVal, double &bVal, ini::DoubleTuple ambientReflection, ini::DoubleTuple diffuseReflection, ini::DoubleTuple specularReflection, double reflectionCoeff, Vector3D A, Vector3D B, Vector3D C, Vector3D pixel) const {
    applyAmbientLight(rVal, gVal, bVal, ambientLight, ambientReflection);
    applyDiffuseLight(rVal, gVal, bVal, diffuseLight, diffuseReflection, Calculator::calcNormal(A, B, C), ldVector);
}

void InfLight::applyTransformation(Matrix m) {
    ldVector *= m;
}

void InfLight::applyDiffuseLight(double &rVal, double &gVal, double &bVal, const ini::DoubleTuple &diffuseLight, const ini::DoubleTuple &diffuseReflection, Vector3D normal, Vector3D ldVector) {
    Vector3D l = Vector3D::normalise(-ldVector);
    double cosAlpha = Vector3D::dot(normal,l);

    if (cosAlpha<0) return;

    rVal += diffuseReflection[0] * cosAlpha * diffuseLight[0];
    gVal += diffuseReflection[1] * cosAlpha * diffuseLight[1];
    bVal += diffuseReflection[2] * cosAlpha * diffuseLight[2];
}

InfLight::InfLight(const ini::DoubleTuple &ambientLight, const ini::DoubleTuple &diffuseLight, const Vector3D &ldVector) : AmbientLight(ambientLight), diffuseLight(diffuseLight), ldVector(ldVector) {}


void PointLight::calculateColor(double &rVal, double &gVal, double &bVal, ini::DoubleTuple ambientReflection, ini::DoubleTuple diffuseReflection, ini::DoubleTuple specularReflection, double reflectionCoeff, Vector3D A, Vector3D B, Vector3D C, Vector3D pixel) const {
    applyAmbientLight(rVal, gVal, bVal, ambientLight, ambientReflection);
    applyDiffuseLight(rVal, gVal, bVal, diffuseLight, diffuseReflection, pixel, Calculator::calcNormal(A, B, C), location, spotAngle);
}

void PointLight::applyTransformation(Matrix m) {
    location *= m;
}

void PointLight::applyDiffuseLight(double &rVal, double &gVal, double &bVal, const ini::DoubleTuple &diffuseLight, const ini::DoubleTuple &diffuseReflection, Vector3D pixel, Vector3D normal, Vector3D location, double spotAngle) {
    Vector3D l = Vector3D::normalise(location - pixel);
    double cosAlpha = Vector3D::dot(normal, l);

    if (cosAlpha<0) return;

    double factor = (spotAngle == -1) ? cosAlpha : (1 - (1 - cosAlpha) / (1 - cos(Calculator::degToRad(spotAngle))));

    rVal += diffuseReflection[0] * factor * diffuseLight[0];
    gVal += diffuseReflection[1] * factor * diffuseLight[1];
    bVal += diffuseReflection[2] * factor * diffuseLight[2];
}

PointLight::PointLight(const ini::DoubleTuple &ambientLight, const ini::DoubleTuple &diffuseLight, const Vector3D &location, double spotAngle) : AmbientLight(ambientLight), diffuseLight(diffuseLight), location(location), spotAngle(spotAngle) {}


void SpecularLight::calculateColor(double &rVal, double &gVal, double &bVal, ini::DoubleTuple ambientReflection, ini::DoubleTuple diffuseReflection, ini::DoubleTuple specularReflection, double reflectionCoeff, Vector3D A, Vector3D B, Vector3D C, Vector3D pixel) const {
    applyAmbientLight(rVal, gVal, bVal, ambientLight, ambientReflection);
    applyDiffuseLight(rVal, gVal, bVal, diffuseLight, diffuseReflection, pixel, Calculator::calcNormal(A, B, C), location, spotAngle);
    applySpecularLight(rVal, gVal, bVal, specularLight, specularReflection, reflectionCoeff, pixel, Calculator::calcNormal(A, B, C), location);
}

void SpecularLight::applySpecularLight(double &rVal, double &gVal, double &bVal, const ini::DoubleTuple &specularLight, const ini::DoubleTuple &specularReflection, const double &reflectionCoeff, Vector3D pixel, Vector3D normal, Vector3D location) {
    Vector3D l = Vector3D::normalise(location - pixel);
    double cosAlpha = Vector3D::dot(normal, l);

    Vector3D r = 2*cosAlpha*normal-l;
    Vector3D camVec = Vector3D::normalise(Vector3D::point(0,0,0)-pixel);
    double cosBeta = Vector3D::dot(r,camVec);

    if (cosBeta<0) return;

    double specularIntensity = std::pow(cosBeta,reflectionCoeff);

    rVal += specularReflection[0] * specularIntensity * specularLight[0];
    gVal += specularReflection[1] * specularIntensity * specularLight[1];
    bVal += specularReflection[2] * specularIntensity * specularLight[2];

    rVal = std::min(std::max(rVal, 0.0), 1.0);
    gVal = std::min(std::max(gVal, 0.0), 1.0);
    bVal = std::min(std::max(bVal, 0.0), 1.0);
}

SpecularLight::SpecularLight(const ini::DoubleTuple &ambientLight, const ini::DoubleTuple &diffuseLight, const ini::DoubleTuple &specularLight, const Vector3D &location) : PointLight(ambientLight, diffuseLight, location, -1), specularLight(specularLight) {}