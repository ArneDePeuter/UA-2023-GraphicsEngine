#ifndef ENGINE_SCENE_H
#define ENGINE_SCENE_H

#include "vector"
#include "Camera.h"
#include "Object3D.h"

class Scene {
public:
    Objects3D objects3D;
    Camera camera;
    void triangulate();
    std::vector<std::vector<Vector3D>> getTriangles();
};


#endif //ENGINE_SCENE_H
