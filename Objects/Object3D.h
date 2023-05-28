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
    Object3D();

    std::vector<Vector3D> vertexes;
    std::vector<Face> faces;

    void applyTransformation(const Matrix &m);
    void applyPoints(const std::vector<double> &v);
    void applyFaces(const std::vector<int> &v, const int &faces, const int &points);
    void triangulate();

    std::vector<Triangle> getTriangles() const;

    Vector3D center;
    img::Color color;

    ini::DoubleTuple ambientReflection;
    ini::DoubleTuple diffuseReflection;
    ini::DoubleTuple specularReflection;
    double reflectionCoefficient;

    static Vector3D getMiddlePoint(const Object3D &object);

    class Object3DFactory {
    public:
        static Object3D load(const std::string &name, const ini::Section &section);

        static std::vector<double> getIcoSahedronPoints();

        static Object3D createLineDrawing(const ini::Section &objsec);
        static Object3D createTetrahedron();
        static Object3D createCube();
        static Object3D createIcosahedron();
        static Object3D createDodecahedron();
        static Object3D createOctahedron();
        static Object3D createCylinder(const int &n, const double &h);
        static Object3D createCone(const int &n, const double &h);
        static Object3D createSphere(const int &n);
        static Object3D createTorus(const double &r, const double &R, const int &n, const int &m);
        static Object3D createBuckyBall();
        static Object3D createLSystem3D(const std::string &filename);
        static Object3D loadObj(const std::string &filename);

        static Object3D fractalize(const double &fractalScale, const int &nrIterations, Object3D fractalObject);
        static Object3D createFractalCube(const double &fractalScale, const int &nrIterations);
        static Object3D createFractalDodecahedron(const double &fractalScale, const int &nrIterations);
        static Object3D createFractalIcosahedron(const double &fractalScale, const int &nrIterations);
        static Object3D createFractalOctahedron(const double &fractalScale, const int &nrIterations);
        static Object3D createFractalTetrahedron(const double &fractalScale, const int &nrIterations);
        static Object3D createMenger(const int &nrIterations);
        static Object3D createFractalBuckyBall(const double &fractalScale, const int &nrIterations);
    };
};

typedef std::list<Object3D> Objects3D;

#endif //ENGINE_OBJECT3D_H
