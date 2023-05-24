#ifndef ENGINE_TRIANGLE_H
#define ENGINE_TRIANGLE_H

#include "vector"
#include "../Include/vector3d.h"
#include "../Include/easy_image.h"

class Triangle {
public:
    Vector3D A;
    Vector3D B;
    Vector3D C;

    ini::DoubleTuple ambientReflection;
    ini::DoubleTuple diffuseReflection;
    ini::DoubleTuple specularReflection;
    double reflectionCoefficient;
};


#endif //ENGINE_TRIANGLE_H
