#ifndef ENGINE_LIGHT_H
#define ENGINE_LIGHT_H

#include <list>
#include "../Include/vector3d.h"
#include "../Include/easy_image.h"
#include "../Include/ini_configuration.h"
#include "Calculator.h"
#include "ZBuffer.h"

class Object3D;

class Light {
public:
    virtual ~Light() = default;
    virtual void calculateColor(double &rVal, double &gVal, double &bVal, ini::DoubleTuple ambientReflection, ini::DoubleTuple diffuseReflection, ini::DoubleTuple specularReflection, double reflectionCoeff, Vector3D A, Vector3D B, Vector3D C, Vector3D pixelEye) const = 0;
    virtual void applyTransformation(Matrix m)=0;
    virtual void initFully(const std::list<Object3D> &objects){};
};

class AmbientLight : public Light {
public:
    explicit AmbientLight(const ini::DoubleTuple &ambientLight);

    void calculateColor(double &rVal, double &gVal, double &bVal, ini::DoubleTuple ambientReflection, ini::DoubleTuple diffuseReflection, ini::DoubleTuple specularReflection, double reflectionCoeff, Vector3D A, Vector3D B, Vector3D C, Vector3D pixelEye) const override;
    void applyTransformation(Matrix m) override;

    void applyAmbientLight(double &rVal, double &gVal, double &bVal, const ini::DoubleTuple &ambientReflection) const;

public:
    ini::DoubleTuple ambientLight;
};


class InfLight : public AmbientLight {
public:
    InfLight(const ini::DoubleTuple &ambientLight, const ini::DoubleTuple &diffuseLight,
             const ini::DoubleTuple &specularLight, const Vector3D &ldVector);

    void calculateColor(double &rVal, double &gVal, double &bVal, ini::DoubleTuple ambientReflection, ini::DoubleTuple diffuseReflection, ini::DoubleTuple specularReflection, double reflectionCoeff, Vector3D A, Vector3D B, Vector3D C, Vector3D pixelEye) const override;
    void applyTransformation(Matrix m) override;

    void applyDiffuseLight(double &rVal, double &gVal, double &bVal, const ini::DoubleTuple &diffuseReflection, Vector3D normal) const;
    void applySpecularLight(double &rVal, double &gVal, double &bVal, const ini::DoubleTuple &specularReflection, const double &reflectionCoeff, Vector3D pixel, Vector3D normal) const;

public:
    ini::DoubleTuple diffuseLight;
    ini::DoubleTuple specularLight;
    Vector3D ldVector;
};

class PointLight : public AmbientLight {
public:
    PointLight(const ini::DoubleTuple &ambientLight, const ini::DoubleTuple &diffuseLight,
               const ini::DoubleTuple &specularLight, const Vector3D &location, double spotAngle);

    void calculateColor(double &rVal, double &gVal, double &bVal, ini::DoubleTuple ambientReflection, ini::DoubleTuple diffuseReflection, ini::DoubleTuple specularReflection, double reflectionCoeff, Vector3D A, Vector3D B, Vector3D C, Vector3D pixelEye) const override;
    void applyTransformation(Matrix m) override;

    void applyDiffuseLight(double &rVal, double &gVal, double &bVal, const ini::DoubleTuple &diffuseReflection, Vector3D pixel, Vector3D normal) const;
    void applySpecularLight(double &rVal, double &gVal, double &bVal, const ini::DoubleTuple &specularReflection, const double &reflectionCoeff, Vector3D pixel, Vector3D normal) const;

public:
    ini::DoubleTuple diffuseLight;
    ini::DoubleTuple specularLight;
    Vector3D location;
    double spotAngle;
};

class ShadowPointLight : public PointLight {
public:
    ShadowPointLight(const ini::DoubleTuple &ambientLight, const ini::DoubleTuple &diffuseLight,
                     const ini::DoubleTuple &specularLight, const Vector3D &location, double spotAngle, int bufferSize,
                     const Matrix &eye);

    void initFully(const std::list<Object3D> &objects) override;
    void calculateColor(double &rVal, double &gVal, double &bVal, ini::DoubleTuple ambientReflection, ini::DoubleTuple diffuseReflection, ini::DoubleTuple specularReflection, double reflectionCoeff, Vector3D A, Vector3D B, Vector3D C, Vector3D pixelEye) const override;
    bool applyLight(const Vector3D& pixel) const;
    void fillBuffer(const std::vector<Triangle> &triangles);

    Vector3D worldLocation;
    int bufferSize;
    ZBuffer shadowMask = ZBuffer(0, 0);
    Matrix inverseEye;
    Matrix lightEye;
    double d=0, dx=0, dy=0;
};

typedef std::vector<Light*> lights3D;

#endif //ENGINE_LIGHT_H