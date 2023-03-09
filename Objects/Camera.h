#ifndef ENGINE_CAMERA_H
#define ENGINE_CAMERA_H

#include "Calculator.h"
#include "../Include/ini_configuration.h"
#include "../Include/vector3d.h"
#include "Object3D.h"

class Camera {
public:
    explicit Camera(const ini::DoubleTuple &pos) {
        position = Vector3D::point(pos[0], pos[1], pos[2]);
    }
    Camera() {};

    void eyePointTransform(Objects3D &objects) const {
        Matrix eyeMatrix = Calculator::eyePointMatrix(position);
        for (Object3D &obj : objects) {
            obj.applyTransformation(eyeMatrix);
        }
    };

    Vector3D position;
};



#endif //ENGINE_CAMERA_H
