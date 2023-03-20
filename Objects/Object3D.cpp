#include <fstream>
#include "Object3D.h"
#include "Calculator.h"
#define _USE_MATH_DEFINES
#include "cmath"
#include "../Include/obj_parser.h"


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

Object3D Object3D::createCube() {
    Object3D cube;
    cube.applyPoints({
            1, -1, 1, -1,  1, -1,  1, -1,
            -1,  1, 1, -1,  1, -1, -1,  1,
            -1, -1, 1,  1, -1, -1,  1,  1,
    });
    cube.applyFaces({
           0, 4, 1, 5, 6, 0,
           4, 1, 5, 0, 2, 5,
           2, 7, 3, 6, 7, 1,
           6, 2, 7, 3, 3, 4
    }, 6,4);
    return cube;
}

Object3D Object3D::createTetrahedron() {
    Object3D tetrahedron;
    tetrahedron.applyPoints({
         1, -1, 1, -1,
        -1,  1, 1, -1,
        -1, -1, 1,  1
    });
    tetrahedron.applyFaces({
        0, 1, 0, 0,
        1, 3, 3, 2,
        2, 2, 1, 3
    }, 4 ,3);
    return tetrahedron;
}

Object3D Object3D::createOctahedron() {
    Object3D octahedron;
    octahedron.applyPoints({
            1, 0, -1,  0,  0, 0,
            0, 1,  0, -1,  0, 0,
            0, 0,  0,  0, -1, 1,
    });
    octahedron.applyFaces({
           0, 1, 2, 3, 1, 2, 3, 0,
           1, 2, 3, 0, 0, 1, 2, 3,
           5, 5, 5, 5, 4, 4, 4, 4
    }, 8, 3);
    return octahedron;
}

std::vector<double> Object3D::getIcoSahedronPoints() {
    std::vector<double> v {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    for (int i = 1; i <= 12; i++) {
        double x, y, z;
        if (i==1) {
            x = 0;
            y = 0;
            z = sqrt(5)/2;
        }
        else if (i>=2 && i<=6) {
            x = cos((i-2)*2*M_PI/5);
            y = sin((i-2)*2*M_PI/5);
            z = 0.5;
        }
        else if (i>=7 && i<=11) {
            x = cos(M_PI/5 + (i-7)*2*M_PI/5);
            y = sin(M_PI/5 + (i-7)*2*M_PI/5);
            z = -0.5;
        }
        else if (i==12) {
            x = 0;
            y = 0;
            z = -sqrt(5)/2;
        }
        v[i-1] = x;
        v[i+12-1] = y;
        v[i+12*2-1] = z;
    }
    return v;
}

Object3D Object3D::createIcosahedron() {
    Object3D icosahedron;
    icosahedron.applyPoints(getIcoSahedronPoints());
    icosahedron.applyFaces({
        0, 0, 0, 0, 0, 1, 2, 2, 3, 3,  4,  4,  5,  5,  1, 11, 11, 11, 11, 11,
        1, 2, 3, 4, 5, 6, 6, 7, 7, 8,  8,  9,  9, 10, 10,  7,  8,  9, 10,  6,
        2, 3, 4, 5, 1, 2, 7, 3, 8, 4,  9,  5, 10,  1,  6,  6,  7,  8,  9, 10,
   }, 20, 3);
    return icosahedron;
}

Object3D Object3D::createDodecahedron() {
    Object3D dodecahedron = createIcosahedron();
    std::vector<double> v {
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    for (int i = 0; i < 20; i++) {
        Face f = dodecahedron.faces[i];
        double x, y, z;
        std::vector<Vector3D> vert = dodecahedron.vertexes;
        x = vert[f.point_indexes[0]].x + vert[f.point_indexes[1]].x + vert[f.point_indexes[2]].x;
        x /= 3;

        y = vert[f.point_indexes[0]].y + vert[f.point_indexes[1]].y + vert[f.point_indexes[2]].y;
        y /= 3;

        z = vert[f.point_indexes[0]].z + vert[f.point_indexes[1]].z + vert[f.point_indexes[2]].z;
        z /= 3;

        v[i] = x;
        v[i+20] = y;
        v[i+20*2] = z;
    }
    dodecahedron.applyPoints(v);
    dodecahedron.applyFaces({
        0, 0,  1,  2,  3,  4, 19, 19, 18, 17, 16, 15,
        1, 5,  7,  9, 11, 13, 18, 14, 12, 10,  8,  6,
        2, 6,  8, 10, 12, 14, 17, 13, 11,  9,  7,  5,
        3, 7,  9, 11, 13,  5, 16, 12, 10,  8,  6, 14,
        4, 1,  2,  3,  4,  0, 15, 18, 17, 16, 15, 19
    }, 12, 5);
    return dodecahedron;
}

Object3D Object3D::createSphere(const int n) {
    Object3D sphere = createIcosahedron();
    for (int i = 0; i < n; i++) {
        std::vector<Face> newFaces;
        for (Face f:sphere.faces) {
            f.subdivide(sphere.vertexes, newFaces);
        }
        sphere.faces = newFaces;
    }
    for (Vector3D &v:sphere.vertexes) {
        v.normalise();
    }
    return sphere;
}

Object3D Object3D::createTorus(const double r, const double R, const int n, const int m) {
    Object3D torus;
    double v, u;
    double x, y, z;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            v = (2*M_PI*i)/n;
            u = (2*M_PI*j)/m;
            x = (R + r * cos(v)) * cos(u);
            y = (R + r * cos(v)) * sin(u);
            z = r * sin(v);
            torus.vertexes.push_back(Vector3D::point(x, y, z));
            torus.faces.push_back(Face({i*m+j, ((i+1)%n)*m+j, ((i+1)%n)*m+(j+1)%m, i*m+(j+1)%m}));
        }
    }
    return torus;
}

Object3D Object3D::createCylinder(const int n, const double h) {
    Object3D cylinder;

    for (int i = 0; i <= n; i++) {
        cylinder.vertexes.push_back(Vector3D::point(cos((M_PI*2*i)/n), sin((M_PI*2*i)/n),0));
        cylinder.vertexes.push_back(Vector3D::point(cos((M_PI*2*i)/n), sin((M_PI*2*i)/n),h));
    }

    std::vector<int> top_ids;
    std::vector<int> bot_ids;
    for (int i = 0; i <= 2*n-4; i+=2) {
        cylinder.faces.push_back(Face({i, i+2, i+3, i+1}));
        bot_ids.push_back(i);
        top_ids.push_back(i+1);
    }
    cylinder.faces.push_back(Face({2*n-2, 0, 1, 2*n-1}));

    top_ids.push_back(2*n-1);
    bot_ids.push_back(2*n-2);
    cylinder.faces.push_back(Face({top_ids}));
    cylinder.faces.push_back(Face({bot_ids}));
    return cylinder;
}

Object3D Object3D::createCone(const int n, const double h) {
    Object3D cone;

    Vector3D pn = Vector3D::point(0, 0,h);
    for (int i = 0; i <= n; i++) {
        cone.vertexes.push_back(Vector3D::point(cos((M_PI*2*i)/n), sin((M_PI*2*i)/n),0));
    }
    cone.vertexes.push_back(pn);

    for (int i = 0; i <= n; i++) {
        cone.faces.push_back(Face({i,(i+1)%n,n+1}));
    }
    std::vector<int> pointIndexes;
    for (int i = n-1; i >= 0; i--) {
        pointIndexes.push_back(i);
    }
    cone.faces.push_back(Face(pointIndexes));
    return cone;
}

Object3D Object3D::loadObj(const std::string &filename) {
    Object3D obj;
    obj::OBJFile obj_parser;
    std::ifstream input_stream(filename);
    input_stream>>obj_parser;
    input_stream.close();

    obj::ObjectGroup object = obj_parser.get_object();

    std::vector<std::vector<double>> vectVertexes = object.get_vertexes();
    for (std::vector<double> vertex:vectVertexes) {
        if (vertex.size()==3){
            obj.vertexes.push_back(Vector3D::point(vertex[0], vertex[1], vertex[3]));
        }
    }
    std::vector<obj::Polygon> polygons = object.get_polygons();
    for (obj::Polygon p:polygons){
        obj.faces.push_back(Face(p.get_indexes()));
    }
}

Object3D Object3D::createLineDrawing(const ini::Section &objsec) {
    Object3D linedrawing;
    int nrPoints = objsec["nrPoints"].as_int_or_die();
    int nrLines = objsec["nrLines"].as_int_or_die();

    for (int i = 0; i < nrPoints; i++) {
        ini::DoubleTuple pointCoords = objsec["point" + std::to_string(i)].as_double_tuple_or_die();
        Vector3D point = Vector3D::point(pointCoords[0], pointCoords[1], pointCoords[2]);
        linedrawing.vertexes.push_back(point);
    }

    for (int i = 0; i < nrLines; i++) {
        ini::IntTuple indexes = objsec["line" + std::to_string(i)].as_int_tuple_or_die();
        Face f({indexes[0], indexes[1]});
        linedrawing.faces.push_back(f);
    }
    return linedrawing;
}




