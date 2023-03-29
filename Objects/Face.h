#ifndef ENGINE_FACE_H
#define ENGINE_FACE_H

#include "../Include/vector3d.h"
#include <vector>

class Face {
public:
    explicit Face(const std::vector<int> &pointIndexes) : point_indexes(pointIndexes){};
    std::vector<int> point_indexes;
    void subdivide(std::vector<Vector3D> &vertexes, std::vector<Face> &newFaces);
    void triangulate(std::vector<Face> &newFaces);
};

#endif //ENGINE_FACE_H
