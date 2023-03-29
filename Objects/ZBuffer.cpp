#include <iostream>
#include "ZBuffer.h"

ZBuffer::ZBuffer(const int &width, const int &heigth) {
    for (int i = 0; i < heigth; i++) {
        std::vector<double> row;
        for (int j = 0; j < width; j++) {
            row.push_back(std::numeric_limits<double>::infinity());
        }
        this->push_back(row);
    }
}

bool ZBuffer::apply(const unsigned int &x, const unsigned int &y, const double &zA, const double &zB, const unsigned int &a, unsigned int &i) {
    double bufVal = calculateVal(zA, zB, a, i);
    i--;

    if (bufVal < (*this)[y][x]) {
        (*this)[y][x] = bufVal;
        return true;
    }
    return false;
}

double ZBuffer::calculateVal(const double &zA, const double &zB, const unsigned int &a, const unsigned int &i) {
    double t = (double)i/(double)a;
    return t/zA + (1-t)/zB;
}

bool ZBuffer::apply(const unsigned int &x, const unsigned int &y, const double &bufVal) {
    if (bufVal < (*this)[y][x]) {
        (*this)[y][x] = bufVal;
        return true;
    }
    return false;
}
