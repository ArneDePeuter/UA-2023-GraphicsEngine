#include "Object3D.h"
#include "../Include/Calculator.h"

Object3D::Object3D(ini::Section &objsec) {
    int rotateX = objsec["rotateX"].as_int_or_die();
    int rotateY = objsec["rotateY"].as_int_or_die();
    int rotateZ = objsec["rotateZ"].as_int_or_die();
    double scale = objsec["scale"].as_double_or_die();

    ini::IntTuple centertuple = objsec["center"].as_int_tuple_or_die();
    center = Vector3D::point(centertuple[0], centertuple[1], centertuple[2]);

    ini::DoubleTuple colorTuple = objsec["color"].as_double_tuple_or_die();
    color = img::Color(colorTuple[0]*255, colorTuple[1]*255, colorTuple[2]*255);

    int nrPoints = objsec["nrPoints"].as_int_or_die();
    int nrLines = objsec["nrLines"].as_int_or_die();

    for (int i = 0; i < nrPoints; i++) {
        ini::DoubleTuple pointCoords = objsec["point" + std::to_string(i)].as_double_tuple_or_die();
        Vector3D point = Vector3D::point(pointCoords[0], pointCoords[1], pointCoords[2]);
        vertexes.push_back(point);
    }

    for (int i = 0; i < nrLines; i++) {
        ini::IntTuple indexes = objsec["line" + std::to_string(i)].as_int_tuple_or_die();
        Face f({indexes[0], indexes[1]});
        faces.push_back(f);
    }

    initTransform(scale, rotateX, rotateY, rotateZ);
}

void Object3D::applyTransformation(const Matrix &m) {
    for (Vector3D &vertex : vertexes) {
        vertex *= m;
    }
    center *= m;
}

void Object3D::initTransform(double s, int rx, int ry, int rz) {
    applyTransformation(Calculator::superMatrix(s, rx, ry, rz));
}
