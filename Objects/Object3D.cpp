#include "Object3D.h"
#include "Triangle.h"

Object3D::Object3D() {}

void Object3D::applyTransformation(const Matrix &m) {
    for (Vector3D &vertex : vertexes) {
        vertex *= m;
    }
    center *= m;
}

void Object3D::applyPoints(const std::vector<double> &v) {
    int width = v.size() / 3;
    for (int i = 0; i < width; i++) {
        vertexes.push_back(Vector3D::point(v[i], v[i+width], v[i+width*2]));
    }
}

void Object3D::applyFaces(const std::vector<int> &v, const int &facesAmount, const int &pointsAmount) {
    for (int i = 0; i < facesAmount; i++) {
        std::vector<int> pointIndexes;
        for (int j = 0; j < pointsAmount; j++) {
            pointIndexes.push_back(v[i+j*facesAmount]);
        }
        faces.push_back(Face(pointIndexes));
    }
}

std::vector<Triangle> Object3D::getTriangles() const {
    std::vector<Triangle> triangles;
    for (const Face &f:faces) {
        Triangle t;
        t.A = vertexes[f.point_indexes[0]];
        t.B = vertexes[f.point_indexes[1]];
        t.C = vertexes[f.point_indexes[2]];
        t.ambientReflection = ambientReflection;
        t.reflectionCoefficient = reflectionCoefficient;
        t.specularReflection = specularReflection;
        t.diffuseReflection = diffuseReflection;
        triangles.push_back(t);
    }
    return triangles;
}

Vector3D Object3D::getMiddlePoint(const Object3D &object) {
    Vector3D mid;
    for (const Vector3D &vertex:object.vertexes) {
        mid.x += vertex.x;
        mid.y += vertex.y;
        mid.z += vertex.z;
    }
    mid.x /= object.vertexes.size();
    mid.y /= object.vertexes.size();
    mid.z /= object.vertexes.size();

    return mid;
}
