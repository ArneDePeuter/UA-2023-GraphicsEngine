#ifndef ENGINE_LIGHT_H
#define ENGINE_LIGHT_H

#include "../Include/vector3d.h"
#include "../Include/easy_image.h"
#include "../Include/ini_configuration.h"
#include "Calculator.h"
#include "ZBuffer.h"

class Light {
public:
    virtual ~Light() = default;
    virtual void calculateColor(double &rVal, double &gVal, double &bVal, ini::DoubleTuple ambientReflection, ini::DoubleTuple diffuseReflection, ini::DoubleTuple specularReflection, double reflectionCoeff, Vector3D A, Vector3D B, Vector3D C) const = 0;
    virtual void applyTransformation(Matrix m)=0;
    virtual void initFully(const double &d, const double &dx, const double &dy){};
};

class AmbientLight : public Light {
public:
    explicit AmbientLight(const ini::DoubleTuple &ambientLight);

    void calculateColor(double &rVal, double &gVal, double &bVal, ini::DoubleTuple ambientReflection, ini::DoubleTuple diffuseReflection, ini::DoubleTuple specularReflection, double reflectionCoeff, Vector3D A, Vector3D B, Vector3D C) const override;
    void applyTransformation(Matrix m) override;
    static void applyAmbientLight(double &rVal, double &gVal, double &bVal, const ini::DoubleTuple &ambientLight, const ini::DoubleTuple &ambientReflection);

    ini::DoubleTuple ambientLight;
};


class InfLight : public AmbientLight {
public:
    InfLight(const ini::DoubleTuple &ambientLight, const ini::DoubleTuple &diffuseLight, const Vector3D &ldVector);

    void calculateColor(double &rVal, double &gVal, double &bVal, ini::DoubleTuple ambientReflection, ini::DoubleTuple diffuseReflection, ini::DoubleTuple specularReflection, double reflectionCoeff, Vector3D A, Vector3D B, Vector3D C) const override;
    void applyTransformation(Matrix m) override;
    static void applyDiffuseLight(double &rVal, double &gVal, double &bVal, const ini::DoubleTuple &diffuseLight, const ini::DoubleTuple &diffuseReflection, Vector3D A, Vector3D B, Vector3D C, Vector3D ldVector);

    ini::DoubleTuple diffuseLight;
    Vector3D ldVector;
};

class PointLight : public AmbientLight {
public:
    PointLight(const ini::DoubleTuple &ambientLight, const ini::DoubleTuple &diffuseLight, const Vector3D &location, double spotAngle);

    void calculateColor(double &rVal, double &gVal, double &bVal, ini::DoubleTuple ambientReflection, ini::DoubleTuple diffuseReflection, ini::DoubleTuple specularReflection, double reflectionCoeff, Vector3D A, Vector3D B, Vector3D C) const override;
    void applyTransformation(Matrix m) override;
    static void applyDiffuseLight(double &rVal, double &gVal, double &bVal, const ini::DoubleTuple &diffuseLight, const ini::DoubleTuple &diffuseReflection, Vector3D A, Vector3D B, Vector3D C, Vector3D location, double spotAngle);

    ini::DoubleTuple diffuseLight;
    Vector3D location;
    double spotAngle;
};

class SpecularLight : public PointLight {
public:
    SpecularLight(const ini::DoubleTuple &ambientLight, const ini::DoubleTuple &diffuseLight, const ini::DoubleTuple &specularLightconst, Vector3D &location);

    void calculateColor(double &rVal, double &gVal, double &bVal, ini::DoubleTuple ambientReflection, ini::DoubleTuple diffuseReflection, ini::DoubleTuple specularReflection, double reflectionCoeff, Vector3D A, Vector3D B, Vector3D C) const override;
    static void applySpecularLight(double &rVal, double &gVal, double &bVal, const ini::DoubleTuple &specularLight, const ini::DoubleTuple &specularReflection, const double &reflectionCoeff, Vector3D A, Vector3D B, Vector3D C, Vector3D location);

    ini::DoubleTuple specularLight;
};

class ShadowPointLight : public PointLight {
public:
    ShadowPointLight(const ini::DoubleTuple &ambientLight, const ini::DoubleTuple &diffuseLight, const Vector3D &location, const ZBuffer &shadowMask, const Matrix &eye);
    void initFully(const double &d, const double &dx, const double &dy) override {this->d=d; this->dx=dx; this->dy=dy;};

    ZBuffer shadowMask;
    Matrix eye;
    double d, dx, dy;
};

typedef std::vector<Light*> lights3D;

#endif //ENGINE_LIGHT_H
