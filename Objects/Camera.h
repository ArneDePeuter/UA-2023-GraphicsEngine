#ifndef ENGINE_CAMERA_H
#define ENGINE_CAMERA_H

#include "Calculator.h"
#include "../Include/ini_configuration.h"
#include "../Include/vector3d.h"
#include "Object3D.h"
#include "cmath"

class Camera {
public:
    explicit Camera(const ini::DoubleTuple &pos, const bool &clipping_, const ini::DoubleTuple &viewDirection_,
                    const int &dNear_, const int &dFar_, const int &hfov_, const double &aspectRatio_) {
        position = Vector3D::point(pos[0], pos[1], pos[2]);

        clipping = clipping_;
        if (!clipping) {
            viewDirection = -position;
        } else {
            viewDirection = Vector3D::vector(viewDirection_[0],viewDirection_[1],viewDirection_[2]);
        }
        dNear = dNear_;
        dFar = dFar_;
        hfov = hfov_;
        aspectRatio = aspectRatio_;
    }
    Camera() {};

    void eyePointTransform(Objects3D &objects) const {
        if (clipping) {
            Vector3D sphereCoordinates;
            double r = viewDirection.length();
            double theta = atan2(position.y,position.x);
            double phi = acos(position.z/r);

            Matrix eyeMatrix = Calculator::eyePointMatrix(theta, phi, r);
            for (Object3D &obj : objects) {
                obj.applyTransformation(eyeMatrix);
            }
            return;
        }

        Matrix eyeMatrix = Calculator::eyePointMatrix(position);
        for (Object3D &obj : objects) {
            obj.applyTransformation(eyeMatrix);
        }
    };

    Vector3D position;
    bool clipping;
    Vector3D viewDirection;
    int dNear;
    int dFar;
    int hfov;
    double aspectRatio;
};



#endif //ENGINE_CAMERA_H
