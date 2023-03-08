#ifndef ENGINE_FACE_H
#define ENGINE_FACE_H

#include <vector>

class Face {
public:
    explicit Face(const std::vector<int> &pointIndexes) : point_indexes(pointIndexes){};
    std::vector<int> point_indexes;
};


#endif //ENGINE_FACE_H
