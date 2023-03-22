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

bool ZBuffer::apply(const int &x, const int &y, const double &zA, const double &zB, const int &a, int &i) {
    double bufval = calculateVal(zA, zB, a, i);
    i--;

    if (bufval < (*this)[y][x]) {
        (*this)[y][x] = bufval;
        return true;
    }
    return false;
}

double ZBuffer::calculateVal(const int &zA, const int &zB, const int &a, const int &i) {
    double t = i/a;
    return t/zA + (1-t)/zB;
}
