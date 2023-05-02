#ifndef ENGINE_LIGHT_H
#define ENGINE_LIGHT_H

#include "../Include/vector3d.h"
#include "../Include/easy_image.h"
#include "../Include/ini_configuration.h"

class Light {
public:
    virtual ~Light() = default;

    ini::DoubleTuple ambientLight;
    ini::DoubleTuple diffuseLight;
    ini::DoubleTuple specularLight;

    virtual void calculateColor(double &rVal, double &gVal, double &bVal, ini::DoubleTuple ambientReflection,
                                ini::DoubleTuple diffuseReflection, ini::DoubleTuple specularReflection,
                                double reflectionCoeff, Vector3D w) const = 0;
};

class AmbientLight : public Light {
public:
    void calculateColor(double &rVal, double &gVal, double &bVal, ini::DoubleTuple ambientReflection, ini::DoubleTuple diffuseReflection, ini::DoubleTuple specularReflection, double reflectionCoeff, Vector3D w) const {
        rVal += ambientReflection[0] * ambientLight[0];
        gVal += ambientReflection[1] * ambientLight[1];
        bVal += ambientReflection[2] * ambientLight[2];
    }
};


class InfLight : public Light {
public:
    Vector3D ldVector;
    void calculateColor(double &rVal, double &gVal, double &bVal, ini::DoubleTuple ambientReflection, ini::DoubleTuple diffuseReflection, ini::DoubleTuple specularReflection, double reflectionCoeff, Vector3D w) const override {
        rVal += ambientReflection[0] * ambientLight[0];
        gVal += ambientReflection[1] * ambientLight[1];
        bVal += ambientReflection[2] * ambientLight[2];

        Vector3D n = Vector3D::normalise(w);
        Vector3D l = Vector3D::normalise(-ldVector);
        double alpha = Vector3D::dot(n,l);

        rVal += diffuseReflection[0] * cos(alpha);
        gVal += diffuseReflection[1] * cos(alpha);
        bVal += diffuseReflection[2] * cos(alpha);
    }
};

class PointLight : public Light {
public:
    Vector3D location;
    double spotAngle;
    void calculateColor(double &rVal, double &gVal, double &bVal, ini::DoubleTuple ambientReflection, ini::DoubleTuple diffuseReflection, ini::DoubleTuple specularReflection, double reflectionCoeff, Vector3D w) const override {
        rVal += ambientReflection[0] * ambientLight[0];
        gVal += ambientReflection[1] * ambientLight[1];
        bVal += ambientReflection[2] * ambientLight[2];

        Vector3D n = Vector3D::normalise(w);
        Vector3D l = Vector3D::normalise(-location);
        double alpha = Vector3D::dot(n,l);

        rVal += diffuseReflection[0] * (1-(1-cos(alpha)/(1-cos(spotAngle))));
        gVal += diffuseReflection[1] * (1-(1-cos(alpha)/(1-cos(spotAngle))));
        bVal += diffuseReflection[2] * (1-(1-cos(alpha)/(1-cos(spotAngle))));
    }
};

typedef std::vector<Light*> lights3D;

#endif //ENGINE_LIGHT_H
