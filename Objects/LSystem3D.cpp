#include <fstream>
#include "LSystem3D.h"

LSystem3D::LSystem3D(const std::string &inputfile) {
    parse(inputfile);
    iterate();
    create();
}

void LSystem3D::parse(const std::string &inputfile) {
    std::ifstream input_stream(inputfile);
    input_stream >> lSys;
    input_stream.close();
    alpha = lSys.get_angle();
}

void LSystem3D::iterate() {
    std::string s = lSys.get_initiator();
    for (int i = 0; i < lSys.get_nr_iterations(); i++) {
        std::string newS;
        for (char c : s) {
            if (c != '+' && c != '-' && c != '(' && c != ')'
                && c != '^' && c != '\\' && c != '/' && c != '&' && c != '|') {
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

void LSystem3D::create() {
    for (char c : lString) {
        if (c != '+' && c != '-' && c != '(' && c != ')'
            && c != '^' && c != '\\' && c != '/' && c != '&' && c != '|') {
            if (lSys.draw(c)) {
                vertexes.push_back(pos);
                pos += H;
                vertexes.push_back(pos);
                int id = vertexes.size()-2;
                faces.push_back(Face({id,id+1}));
            } else {
                pos += H;
            }
        }
        else {
            handleSign(c);
        }
    }
}

void LSystem3D::handleSign(const char &c) {
    Vector3D newH;
    Vector3D newL;
    Vector3D newU;
    switch (c) {
        case '+':
            newH = H*cos(Calculator::degToRad(alpha)) + L*sin(Calculator::degToRad(alpha));
            newL = -H*sin(Calculator::degToRad(alpha)) + L*cos(Calculator::degToRad(alpha));
            H = newH;
            L = newL;
            break;
        case '-':
            newH = H*cos(Calculator::degToRad(-alpha)) + L*sin(Calculator::degToRad(-alpha));
            newL = -H*sin(Calculator::degToRad(-alpha)) + L*cos(Calculator::degToRad(-alpha));
            H = newH;
            L = newL;
            break;
        case '(':
            HStack.push(H);
            LStack.push(L);
            UStack.push(U);
            posStack.push(pos);
            break;
        case ')':
            H = HStack.top();
            L = LStack.top();
            U = UStack.top();
            pos = posStack.top();
            HStack.pop();
            LStack.pop();
            UStack.pop();
            posStack.pop();
            break;
        case '^':
            newH = H*cos(Calculator::degToRad(-alpha)) + U*sin(Calculator::degToRad(-alpha));
            newU = -H*sin(Calculator::degToRad(-alpha)) + U*cos(Calculator::degToRad(-alpha));
            U = newU;
            H = newH;
            break;
        case '&':
            newH = H*cos(Calculator::degToRad(alpha)) + U*sin(Calculator::degToRad(alpha));
            newU = -H*sin(Calculator::degToRad(alpha)) + U*cos(Calculator::degToRad(alpha));
            U = newU;
            H = newH;
            break;
        case '\\':
            newU = L*sin(Calculator::degToRad(-alpha)) + U*cos(Calculator::degToRad(-alpha));
            newL = L*cos(Calculator::degToRad(-alpha)) - U*sin(Calculator::degToRad(-alpha));
            L = newL;
            U = newU;
            break;
        case '/':
            newU = L*sin(Calculator::degToRad(alpha)) + U*cos(Calculator::degToRad(alpha));
            newL = L*cos(Calculator::degToRad(alpha)) - U*sin(Calculator::degToRad(alpha));
            L = newL;
            U = newU;
            break;
        case '|':
            H = -H;
            L = -L;
            break;
        default:
            break;
    }
}
