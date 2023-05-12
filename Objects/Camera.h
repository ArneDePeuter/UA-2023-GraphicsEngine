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
        if (settings.clipping) {
            return;
//            Vector3D sphereCoordinates;
//            double r = viewDirection.length();
//            double theta = atan2(position.y,position.x);
//            double phi = acos(position.z/r);
//
//            Matrix eyeMatrix = Calculator::eyePointMatrix(theta, phi, r);
//            for (Object3D &obj : objects) {
//                obj.applyTransformation(eyeMatrix);
//            }
//            return;
        }

        for (Object3D &obj : objects) {
            obj.applyTransformation(eyeMatrix);
        }
    };

    void eyePointTransformLights(std::vector<Light*> &lights) const {
        for (Light *light : lights) {
            light->applyTransformation(eyeMatrix);
        }
    }

    Matrix eyeMatrix;
    Vector3D position;
    ClippingSettings settings;
};



#endif //ENGINE_CAMERA_H
