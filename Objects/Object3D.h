#ifndef ENGINE_OBJECT3D_H
#define ENGINE_OBJECT3D_H

#include "../Include/easy_image.h"
#include "../Include/ini_configuration.h"
#include "../Include/vector3d.h"
#include "Face.h"
#include <vector>
#include <list>

class Object3D {
public:
    explicit Object3D(ini::Section &objsec);
    Object3D(const int &rotateX, const int &rotateY, const int &rotateZ, const double &scale, const Vector3D &center, const img::Color &color);

    std::vector<Vector3D> vertexes;
    std::vector<Face> faces;

    void applyTransformation(const Matrix &m);
    void applyPoints(const std::vector<double> &v);
    void applyFaces(const std::vector<int> &v, const int &faces, const int &points);

    void createLineDrawing(ini::Section &objsec);
    void createTetrahedron();
    std::vector<double> getIcoSahedronPoints();
    void createCube();
    void createIcosahedron();
    void createDodecahedron();
    void createOctahedron();
    void createCylinder(const int n, const double h);
    void createCone(const int n, const double h);
    void createSphere(const int n);
    void createTorus(const double r, const double R, const int n, const int m);
    void loadObj(const std::string &filename);

    Vector3D center;
    img::Color color;
};

typedef std::list<Object3D> Objects3D;

class Cube : public Object3D {
public:
    Cube(const int &rotateX, const int &rotateY, const int &rotateZ, const double &scale, const Vector3D &center,
         const img::Color &color);
};

#endif //ENGINE_OBJECT3D_H
