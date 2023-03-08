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
    std::vector<Vector3D> vertexes;
    std::vector<Face> faces;

    void initTransform(double scale, int rotateX, int rotateY, int rotateZ);
    void applyTransformation(const Matrix &m);

    Vector3D center;
    img::Color color;
};

typedef std::list<Object3D> Objects3D;

#endif //ENGINE_OBJECT3D_H
