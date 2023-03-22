#ifndef ENGINE_LSYSTEM3D_H
#define ENGINE_LSYSTEM3D_H

#include "string"
#include "../Include/easy_image.h"
#include "../Include/l_parser.h"
#include "stack"
#include "Object3D.h"
#include "Calculator.h"
#include "cmath"

class LSystem3D : public Object3D {
public:
    explicit LSystem3D(const std::string &inputfile);
    void parse(const std::string &inputfile);
    void iterate();
    void create();
    void handleSign(const char &c);

    Vector3D pos = Vector3D::point(0,0,0);
    Vector3D H = Vector3D::vector(1,0,0);
    Vector3D L = Vector3D::vector(0,1,0);
    Vector3D U = -Vector3D::vector(0,0,1);

    LParser::LSystem3D lSys;
    std::string lString;
    double alpha;

    std::stack<Vector3D> HStack;
    std::stack<Vector3D> LStack;
    std::stack<Vector3D> UStack;
    std::stack<Vector3D> posStack;
};

#endif //ENGINE_LSYSTEM3D_H