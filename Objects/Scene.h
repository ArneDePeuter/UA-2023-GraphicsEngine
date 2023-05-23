#ifndef ENGINE_SCENE_H
#define ENGINE_SCENE_H

#include "vector"
#include "Camera.h"
#include "Object3D.h"
#include "Triangle.h"
#include "Line2D.h"
#include "Light.h"

class Scene {
public:
    Scene(const Objects3D &objects3D, const Camera &camera, const lights3D &lights, const bool &doTriangulate=true);

    virtual ~Scene();
    void triangulate();
    void eyePointTransform();
    Lines2D project(const double &d) const;
    std::vector<Triangle> getTriangles() const;

    static Point2D point3dto2d(Vector3D &point, double d);
    lights3D lights;
    Objects3D objects3D;

    Camera camera;
};


#endif //ENGINE_SCENE_H
