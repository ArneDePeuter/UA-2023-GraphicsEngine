#include "Face.h"

void Face::subdivide(std::vector<Vector3D> &vertexes, std::vector<Face> &newFaces) {
    if (point_indexes.size()!=3) return;

    int idA = point_indexes[0];
    Vector3D A = vertexes[idA];
    int idB = point_indexes[1];
    Vector3D B = vertexes[idB];
    int idC = point_indexes[2];
    Vector3D C = vertexes[idC];

    int size = vertexes.size();
    Vector3D D = (A+B)/2;
    Vector3D E = (A+C)/2;
    Vector3D F = (B+C)/2;

    vertexes.push_back(D);
    int idD = size;
    vertexes.push_back(E);
    int idE = size+1;
    vertexes.push_back(F);
    int idF = size+2;

    Face ADE({idA, idD, idE});
    Face BFD({idB, idF, idD});
    Face CEF({idC, idE, idF});
    Face DFE({idD, idF, idE});

    newFaces.push_back(ADE);
    newFaces.push_back(BFD);
    newFaces.push_back(CEF);
    newFaces.push_back(DFE);
}

void Face::triangulate(std::vector<Face> &newFaces) {
    if (point_indexes.size()==3) {
        newFaces.push_back(*this);
        return;
    }

    for (int i = 1; i <= point_indexes.size()-2; i++) {
        newFaces.push_back(Face({point_indexes[0], point_indexes[i], point_indexes[i+1]}));
    }
}
