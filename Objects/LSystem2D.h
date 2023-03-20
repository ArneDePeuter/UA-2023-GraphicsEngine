#ifndef ENGINE_LSYSTEM2D_H
#define ENGINE_LSYSTEM2D_H

#include "../Include/ini_configuration.h"
#include "../Include/easy_image.h"
#include "../Include/l_parser.h"
#include "Line2D.h"
#include <string>
#include <list>
#include <stack>

class LSystem2D {
public:
    LSystem2D(const std::string &inputfile, img::Color color);
    void parse(const std::string &inputfile);
    void iterate();
    void setLines();

    Lines2D lines;
    int size;
    img::Color backgroundcolor;
    img::Color color;
    LParser::LSystem2D lSys;

    std::string initiator;
    unsigned int iterations;
    std::string lString;
    double delta;
    double alpha;
    std::stack<double> angleStack;
    std::stack<Point2D> pointStack;
};


#endif //ENGINE_LSYSTEM2D_H
