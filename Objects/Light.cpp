#include "Light.h"

void AmbientLight::applyAmbientLight(double &rVal, double &gVal, double &bVal, const ini::DoubleTuple &ambientLight, const ini::DoubleTuple &ambientReflection) {
    rVal += ambientReflection[0] * ambientLight[0];
    gVal += ambientReflection[1] * ambientLight[1];
    bVal += ambientReflection[2] * ambientLight[2];

    rVal = std::min(std::max(rVal, 0.0), 1.0);
    gVal = std::min(std::max(gVal, 0.0), 1.0);
    bVal = std::min(std::max(bVal, 0.0), 1.0);
}

void AmbientLight::calculateColor(double &rVal, double &gVal, double &bVal, ini::DoubleTuple ambientReflection, ini::DoubleTuple diffuseReflection, ini::DoubleTuple specularReflection, double reflectionCoeff, Vector3D A, Vector3D B, Vector3D C) const {
    applyAmbientLight(rVal, gVal, bVal, ambientLight, ambientReflection);
}

void AmbientLight::applyTransformation(Matrix m) {}

AmbientLight::AmbientLight(const ini::DoubleTuple &ambientLight) : ambientLight(ambientLight) {}

void InfLight::calculateColor(double &rVal, double &gVal, double &bVal, ini::DoubleTuple ambientReflection, ini::DoubleTuple diffuseReflection, ini::DoubleTuple specularReflection, double reflectionCoeff, Vector3D A, Vector3D B, Vector3D C) const {
    applyAmbientLight(rVal, gVal, bVal, ambientLight, ambientReflection);
    applyDiffuseLight(rVal, gVal, bVal, diffuseLight, diffuseReflection, A, B, C, ldVector);
}

void InfLight::applyTransformation(Matrix m) {
    ldVector *= m;
}

void InfLight::applyDiffuseLight(double &rVal, double &gVal, double &bVal, const ini::DoubleTuple &diffuseLight, const ini::DoubleTuple &diffuseReflection, Vector3D A, Vector3D B, Vector3D C, Vector3D ldVector) {
    Vector3D n = Vector3D::normalise(Vector3D::cross(B - A, C - A));
    Vector3D l = Vector3D::normalise(-ldVector);
    double cosAlpha = Vector3D::dot(n,l);

    rVal += diffuseReflection[0] * cosAlpha * diffuseLight[0];
    gVal += diffuseReflection[1] * cosAlpha * diffuseLight[1];
    bVal += diffuseReflection[2] * cosAlpha * diffuseLight[2];

    rVal = std::min(std::max(rVal, 0.0), 1.0);
    gVal = std::min(std::max(gVal, 0.0), 1.0);
    bVal = std::min(std::max(bVal, 0.0), 1.0);
}

InfLight::InfLight(const ini::DoubleTuple &ambientLight, const ini::DoubleTuple &diffuseLight, const Vector3D &ldVector) : AmbientLight(ambientLight), diffuseLight(diffuseLight), ldVector(ldVector) {}

void PointLight::calculateColor(double &rVal, double &gVal, double &bVal, ini::DoubleTuple ambientReflection, ini::DoubleTuple diffuseReflection, ini::DoubleTuple specularReflection, double reflectionCoeff, Vector3D A, Vector3D B, Vector3D C) const {
    applyAmbientLight(rVal, gVal, bVal, ambientLight, ambientReflection);
    applyDiffuseLight(rVal, gVal, bVal, diffuseLight, diffuseReflection, A, B, C, location, spotAngle);
}

void PointLight::applyTransformation(Matrix m) {
    location *= m;
}

void PointLight::applyDiffuseLight(double &rVal, double &gVal, double &bVal, const ini::DoubleTuple &diffuseLight, const ini::DoubleTuple &diffuseReflection, Vector3D A, Vector3D B, Vector3D C, Vector3D location, double spotAngle) {
    Vector3D n = Vector3D::normalise(Vector3D::cross(B - A, C - A));
    Vector3D trianglePosition = (A + B + C) / 3;
    Vector3D l = Vector3D::normalise(location - trianglePosition);
    double cosAlpha = Vector3D::dot(n, l);

    double factor = (spotAngle == -1) ? cosAlpha : (1 - (1 - cosAlpha) / (1 - cos(Calculator::degToRad(spotAngle))));

    rVal += diffuseReflection[0] * factor * diffuseLight[0];
    gVal += diffuseReflection[1] * factor * diffuseLight[1];
    bVal += diffuseReflection[2] * factor * diffuseLight[2];

    rVal = std::min(std::max(rVal, 0.0), 1.0);
    gVal = std::min(std::max(gVal, 0.0), 1.0);
    bVal = std::min(std::max(bVal, 0.0), 1.0);
}

PointLight::PointLight(const ini::DoubleTuple &ambientLight, const ini::DoubleTuple &diffuseLight, const Vector3D &location, double spotAngle) : AmbientLight(ambientLight), diffuseLight(diffuseLight), location(location), spotAngle(spotAngle) {}

void SpecularLight::calculateColor(double &rVal, double &gVal, double &bVal, ini::DoubleTuple ambientReflection, ini::DoubleTuple diffuseReflection, ini::DoubleTuple specularReflection, double reflectionCoeff, Vector3D A, Vector3D B, Vector3D C) const {
    applyAmbientLight(rVal, gVal, bVal, ambientLight, ambientReflection);
    applyDiffuseLight(rVal, gVal, bVal, diffuseLight, diffuseReflection, A, B, C, location, spotAngle);
    applySpecularLight(rVal, gVal, bVal, specularLight, specularReflection, reflectionCoeff, A, B, C, location);
}

void SpecularLight::applySpecularLight(double &rVal, double &gVal, double &bVal, const ini::DoubleTuple &specularLight, const ini::DoubleTuple &specularReflection, const double &reflectionCoeff, Vector3D A, Vector3D B, Vector3D C, Vector3D location) {
    Vector3D n = Vector3D::normalise(Vector3D::cross(B - A, C - A));
    Vector3D trianglePosition = (A + B + C) / 3;
    Vector3D l = Vector3D::normalise(location - trianglePosition);
    double cosAlpha = Vector3D::dot(n, l);

    Vector3D r = 2*cosAlpha*n-l;
    Vector3D camVec = Vector3D::normalise(Vector3D::point(0,0,0)-trianglePosition);
    double cosBeta = std::max((double)0, Vector3D::dot(r,camVec));

    double specularIntensity = std::pow(cosBeta,reflectionCoeff);

    rVal += specularReflection[0] * specularIntensity * specularLight[0];
    gVal += specularReflection[1] * specularIntensity * specularLight[1];
    bVal += specularReflection[2] * specularIntensity * specularLight[2];

    rVal = std::min(std::max(rVal, 0.0), 1.0);
    gVal = std::min(std::max(gVal, 0.0), 1.0);
    bVal = std::min(std::max(bVal, 0.0), 1.0);
}

SpecularLight::SpecularLight(const ini::DoubleTuple &ambientLight, const ini::DoubleTuple &diffuseLight, const ini::DoubleTuple &specularLightconst, Vector3D &location) : PointLight(ambientLight, diffuseLight, location, -1), specularLight(specularLight) {}

ShadowPointLight::ShadowPointLight(const ini::DoubleTuple &ambientLight, const ini::DoubleTuple &diffuseLight, const Vector3D &location, const ZBuffer &shadowMask, const Matrix &eye) : PointLight(ambientLight, diffuseLight, location, -1), shadowMask(shadowMask), eye(eye), d(0), dx(0), dy(0) {}
