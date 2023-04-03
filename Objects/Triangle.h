#ifndef ENGINE_TRIANGLE_H
#define ENGINE_TRIANGLE_H

#include "vector"
#include "../Include/vector3d.h"
#include "../Include/easy_image.h"

class Triangle {
public:
    Vector3D A;
    Vector3D B;
    Vector3D C;
    img::Color color;

    void scale(const double &amount) {
        A*=amount;
        B*=amount;
        C*=amount;
    }

    void move(const double &dx, const double &dy) {
        A.x += dx;
        B.x += dx;
        C.x += dx;

        A.y += dy;
        B.y += dy;
        C.y += dy;
    }
};


#endif //ENGINE_TRIANGLE_H
