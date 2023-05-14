#ifndef ENGINE_LIGHT_H
#define ENGINE_LIGHT_H

#include "../Include/vector3d.h"
#include "../Include/easy_image.h"
#include "../Include/ini_configuration.h"
#include "Calculator.h"

class Light {
public:
    virtual ~Light() = default;

    ini::DoubleTuple ambientLight;
    ini::DoubleTuple diffuseLight;
    ini::DoubleTuple specularLight;

    virtual void calculateColor(double &rVal, double &gVal, double &bVal, ini::DoubleTuple ambientReflection,
                                ini::DoubleTuple diffuseReflection, ini::DoubleTuple specularReflection,
                                double reflectionCoeff, Vector3D A, Vector3D B, Vector3D C) const = 0;
    virtual void applyTransformation(Matrix m)=0;
};

class AmbientLight : public Light {
public:
    void calculateColor(double &rVal, double &gVal, double &bVal, ini::DoubleTuple ambientReflection, ini::DoubleTuple diffuseReflection, ini::DoubleTuple specularReflection, double reflectionCoeff, Vector3D A, Vector3D B, Vector3D C) const override {
        rVal += ambientReflection[0] * ambientLight[0];
        gVal += ambientReflection[1] * ambientLight[1];
        bVal += ambientReflection[2] * ambientLight[2];
    }
    void applyTransformation(Matrix m) override{};
};


class InfLight : public Light {
public:
    Vector3D ldVector;
    void calculateColor(double &rVal, double &gVal, double &bVal, ini::DoubleTuple ambientReflection, ini::DoubleTuple diffuseReflection, ini::DoubleTuple specularReflection, double reflectionCoeff, Vector3D A, Vector3D B, Vector3D C) const override {
        rVal += ambientReflection[0] * ambientLight[0];
        gVal += ambientReflection[1] * ambientLight[1];
        bVal += ambientReflection[2] * ambientLight[2];

        Vector3D n = Vector3D::normalise(Vector3D::cross(B - A, C - A));
        Vector3D l = Vector3D::normalise(-ldVector);
        double cosAlpha = Vector3D::dot(n,l);

        rVal += diffuseReflection[0] * cosAlpha * diffuseLight[0];
        gVal += diffuseReflection[1] * cosAlpha * diffuseLight[1];
        bVal += diffuseReflection[2] * cosAlpha * diffuseLight[2];
    }
    void applyTransformation(Matrix m) override{
        ldVector *= m;
    };
};

class PointLight : public Light {
public:
    Vector3D location;
    double spotAngle;
    void calculateColor(double &rVal, double &gVal, double &bVal, ini::DoubleTuple ambientReflection, ini::DoubleTuple diffuseReflection, ini::DoubleTuple specularReflection, double reflectionCoeff, Vector3D A, Vector3D B, Vector3D C) const override {
        rVal += ambientReflection[0] * ambientLight[0];
        gVal += ambientReflection[1] * ambientLight[1];
        bVal += ambientReflection[2] * ambientLight[2];

        Vector3D n = Vector3D::normalise(Vector3D::cross(B - A, C - A));
        Vector3D trianglePosition = (A + B + C) / 3;
        Vector3D l = Vector3D::normalise(location-trianglePosition);
        double cosAlpha = Vector3D::dot(n,l);

        double factor = (spotAngle==-1) ? cosAlpha : (1-(1-cosAlpha)/(1-cos(Calculator::degToRad(spotAngle))));

        rVal += diffuseReflection[0] * factor * diffuseLight[0];
        gVal += diffuseReflection[1] * factor * diffuseLight[1];
        bVal += diffuseReflection[2] * factor * diffuseLight[2];
    }
    void applyTransformation(Matrix m) override {
        location *= m;
    };
};

class SpecularLight : public Light {
public:
    void calculateColor(double &rVal, double &gVal, double &bVal, ini::DoubleTuple ambientReflection, ini::DoubleTuple diffuseReflection, ini::DoubleTuple specularReflection, double reflectionCoeff, Vector3D A, Vector3D B, Vector3D C) const override {

    }

    void applyTransformation(Matrix m) override {

    }
};

typedef std::vector<Light*> lights3D;

#endif //ENGINE_LIGHT_H
