#include "Light.h"


InfLight::InfLight(const ini::DoubleTuple &ambientLight, const ini::DoubleTuple &diffuseLight,
                   const ini::DoubleTuple &specularLight, const Vector3D &ldVector) : AmbientLight(ambientLight),
                                                                                      diffuseLight(diffuseLight),
                                                                                      specularLight(specularLight),
                                                                                      ldVector(ldVector) {}

void InfLight::applyTransformation(Matrix m) {
    ldVector *= m;
}

void InfLight::calculateColor(double &rVal, double &gVal, double &bVal,
                              ini::DoubleTuple ambientReflection,
                              ini::DoubleTuple diffuseReflection,
                              ini::DoubleTuple specularReflection,
                              double reflectionCoeff,
                              Vector3D A, Vector3D B, Vector3D C, Vector3D pixel) const {
    applyAmbientLight(rVal, gVal, bVal, ambientReflection);
    applyDiffuseLight(rVal, gVal, bVal, diffuseReflection, Calculator::calcNormal(A, B, C));
    applySpecularLight(rVal, gVal, bVal, specularReflection, reflectionCoeff, pixel, Calculator::calcNormal(A, B, C));
}


void InfLight::applyDiffuseLight(double &rVal, double &gVal, double &bVal,
                                 const ini::DoubleTuple &diffuseReflection,
                                 Vector3D normal) const {
    Vector3D l = Vector3D::normalise(-ldVector);
    double cosAlpha = Vector3D::dot(normal,l);

    if (cosAlpha<0) return;

    rVal += diffuseReflection[0] * cosAlpha * diffuseLight[0];
    gVal += diffuseReflection[1] * cosAlpha * diffuseLight[1];
    bVal += diffuseReflection[2] * cosAlpha * diffuseLight[2];
}

void InfLight::applySpecularLight(double &rVal, double &gVal, double &bVal,
                                  const ini::DoubleTuple &specularReflection, const double &reflectionCoeff,
                                  Vector3D pixel, Vector3D normal) const {
    Vector3D l = Vector3D::normalise(-ldVector);
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

