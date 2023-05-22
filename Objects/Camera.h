#ifndef ENGINE_CAMERA_H
#define ENGINE_CAMERA_H

#include "Calculator.h"
#include "../Include/ini_configuration.h"
#include "../Include/vector3d.h"
#include "Object3D.h"
#include "cmath"
#include "ClippingSettings.h"
#include "Light.h"

class Camera {
public:
    explicit Camera(const ini::DoubleTuple &pos, const ClippingSettings &settings)
    : position(Vector3D::point(pos[0], pos[1], pos[2])), settings(settings) {
        eyeMatrix = Calculator::eyePointMatrix(position);
    }

    void eyePointTransformObjects(Objects3D &objects) const {
        for (Object3D &obj : objects) {
            obj.applyTransformation(eyeMatrix);
            clipObject(obj);
        }
    };

    void eyePointTransformLights(std::vector<Light*> &lights) const {
        for (Light *light : lights) {
            light->applyTransformation(eyeMatrix);
        }
    }

    void clipObject(Object3D &object) const {
        if (!settings.clipping) return;

        for (Face &f : object.faces) {
            Vector3D A = object.vertexes[f.point_indexes[0]];
            Vector3D B = object.vertexes[f.point_indexes[1]];
            Vector3D C = object.vertexes[f.point_indexes[2]];
        }
    }

    Matrix eyeMatrix;
    Vector3D position;
    ClippingSettings settings;
};



#endif //ENGINE_CAMERA_H
