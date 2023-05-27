#include "Scene.h"

void Scene::triangulate() {
    for (Object3D &obj:objects3D) {
        obj.triangulate();
    }
}

std::vector<Triangle> Scene::getTriangles() const {
    std::vector<Triangle> triangles;
    for (const Object3D &obj:objects3D) {
        std::vector<Triangle> objTriangles = obj.getTriangles();
        triangles.insert(triangles.end(), objTriangles.begin(), objTriangles.end());
    }
    return triangles;
}

Lines2D Scene::project(const double &d) const {
    Lines2D lines;
    for (Object3D obj : objects3D) {
        for (Face f : obj.faces) {
            for (int i = 0; i < f.point_indexes.size()-1; i++) {
                Vector3D p1 = obj.vertexes[f.point_indexes[i]];
                Vector3D p2 = obj.vertexes[f.point_indexes[i+1]];

                Line2D newLine(point3dto2d(p1,d), point3dto2d(p2, d), obj.color);
                lines.push_back(newLine);
            }
            Vector3D p1 = obj.vertexes[f.point_indexes[0]];
            Vector3D p2 = obj.vertexes[f.point_indexes[f.point_indexes.size()-1]];
            Line2D newLine(point3dto2d(p1,d), point3dto2d(p2, d), obj.color);
            lines.push_back(newLine);
        }
    }
    return lines;
}

Point2D Scene::point3dto2d(Vector3D &point, const double d) {
    Point2D p((d*point.x)/-point.z, (d*point.y)/-point.z, point.z);
    return p;
}

Scene::~Scene() {
    for (Light *l:lights) {
        delete l;
    }
}

Scene::Scene(const Objects3D &objects3D, const Camera &camera, const lights3D &lights, const bool &doTriangulate) : objects3D(objects3D), camera(camera), lights(lights) {
    if (doTriangulate) triangulate();
    eyePointTransform();
}

void Scene::eyePointTransform() {
    camera.eyePointTransformObjects(this->objects3D);
    camera.eyePointTransformLights(lights);
}
