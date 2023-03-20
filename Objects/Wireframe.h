#ifndef ENGINE_WIREFRAME_H
#define ENGINE_WIREFRAME_H

#include "../Include/ini_configuration.h"
#include "../Include/easy_image.h"
#include "Object3D.h"
#include "Line2D.h"
#include "Camera.h"
#include <list>

class Wireframe {
public:
    Wireframe();

    Lines2D project(const double d);
    static Point2D point3dto2d(Vector3D & point, const double d);

    Objects3D objects3D;
    int size;
    img::Color backgroundColor;
    Camera camera;
};


#endif //ENGINE_WIREFRAME_H
