#include <fstream>
#include "LSystem2D.h"
#include "Calculator.h"
#include <cmath>

LSystem2D::LSystem2D(ini::Configuration &configuration) {
    size = configuration["General"]["size"].as_int_or_die();

    ini::DoubleTuple colorTuple = configuration["General"]["backgroundcolor"].as_double_tuple_or_die();
    backgroundcolor = img::Color(colorTuple[0]*255, colorTuple[1]*255, colorTuple[2]*255);

    std::string inputfile = configuration["2DLSystem"]["inputfile"].as_string_or_die();
    parse(inputfile);

    colorTuple = configuration["2DLSystem"]["color"].as_double_tuple_or_die();
    color = img::Color(colorTuple[0]*255, colorTuple[1]*255, colorTuple[2]*255);
    iterate();
    setLines();
}


void LSystem2D::parse(const std::string &inputfile) {
    std::ifstream input_stream(inputfile);
    input_stream >> lSys;
    input_stream.close();

    alpha = lSys.get_angle();
    delta = lSys.get_starting_angle();
    initiator = lSys.get_initiator();
    iterations = lSys.get_nr_iterations();
}

void LSystem2D::setLines() {
    double angle = delta, x=0, y=0;

    for (char c : lString) {
        if (c != '+' && c != '-' && c != '(' && c != ')') {
            if (lSys.draw(c)) {
                Point2D p1(x, y);
                x += cos(Calculator::degToRad(angle));
                y += sin(Calculator::degToRad(angle));
                Point2D p2(x, y);
                lines.emplace_back(Line2D(p1, p2, color));
            } else {
                x += cos(Calculator::degToRad(angle));
                y += sin(Calculator::degToRad(angle));
            }
        }
        else {
            if (c == '+' || c == '-'){
                double d = (c=='+') ? alpha : -alpha;
                angle += d;
            }
            else {
                if (c == '(') {
                    angleStack.push(angle);
                    pointStack.push(Point2D(x, y));
                } else {
                    angle = angleStack.top();
                    angleStack.pop();

                    Point2D point = pointStack.top();
                    pointStack.pop();

                    x = point.x;
                    y = point.y;
                }
            }
        }
    }
}

void LSystem2D::iterate() {
    std::string s = initiator;
    for (int i = 0; i < iterations; i++) {
        std::string newS;
        for (char c : s) {
            if (c != '+' && c != '-' && c != '(' && c != ')') {
                std::string replacement = lSys.get_replacement(c);
                newS += replacement;
            } else {
                newS += c;
            }
        }
        s = newS;
    }
    lString = s;
}