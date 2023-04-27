#ifndef ENGINE_LIGHT_H
#define ENGINE_LIGHT_H

#include "../Include/vector3d.h"
#include "../Include/easy_image.h"

class Light {
public:
    img::Color ambientLight;
    img::Color diffuseLight;
    img::Color specularLight;
};

class InfLight : public Light {
public:
    Vector3D ldVector;
};

class PointLight : public Light {
public:
    Vector3D location;
    double spotAngle;
};

typedef std::vector<Light> lights3D;

#endif //ENGINE_LIGHT_H
