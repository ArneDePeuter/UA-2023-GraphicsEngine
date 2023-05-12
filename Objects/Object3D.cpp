#include "Object3D.h"

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
