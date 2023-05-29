#include "Light.h"

AmbientLight::AmbientLight(const ini::DoubleTuple &ambientLight) : ambientLight(ambientLight) {}

void AmbientLight::applyTransformation(Matrix m) {}

void AmbientLight::calculateColor(double &rVal, double &gVal, double &bVal, ini::DoubleTuple ambientReflection, ini::DoubleTuple diffuseReflection, ini::DoubleTuple specularReflection, double reflectionCoeff, Vector3D A, Vector3D B, Vector3D C, Vector3D pixel) const {
    applyAmbientLight(rVal, gVal, bVal, ambientReflection);

    rVal = std::min(std::max(rVal, 0.0), 1.0);
    gVal = std::min(std::max(gVal, 0.0), 1.0);
    bVal = std::min(std::max(bVal, 0.0), 1.0);
}

void AmbientLight::applyAmbientLight(double &rVal, double &gVal, double &bVal,
                                     const ini::DoubleTuple &ambientReflection) const {
    rVal += ambientReflection[0] * ambientLight[0];
    gVal += ambientReflection[1] * ambientLight[1];
    bVal += ambientReflection[2] * ambientLight[2];
}
