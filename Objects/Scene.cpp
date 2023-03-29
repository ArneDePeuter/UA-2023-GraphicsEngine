#include "Scene.h"

void Scene::triangulate() {
    for (Object3D &obj:objects3D) {
        obj.triangulate();
    }
}

std::vector<std::vector<Vector3D>> Scene::getTriangles() {
    std::vector<std::vector<Vector3D>> triangles;
    for (const Object3D &obj:objects3D) {
        for (const Face &f:obj.faces) {
            std::vector<Vector3D> triangle = {
                    obj.vertexes[f.point_indexes[0]],
                    obj.vertexes[f.point_indexes[1]],
                    obj.vertexes[f.point_indexes[2]]
            };
            triangles.push_back(triangle);
        }
    }
    return triangles;
}
