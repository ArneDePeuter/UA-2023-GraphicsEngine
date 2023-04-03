#ifndef ENGINE_SCENE_H
#define ENGINE_SCENE_H

#include "vector"
#include "Camera.h"
#include "Object3D.h"
#include "Triangle.h"
#include "Line2D.h"

class Scene {
public:
    Objects3D objects3D;
    Camera camera;
    void triangulate();
    Lines2D project(const double &d);
    std::vector<Triangle> getTriangles();
    Point2D point3dto2d(Vector3D &point, const double d);
};


#endif //ENGINE_SCENE_H
