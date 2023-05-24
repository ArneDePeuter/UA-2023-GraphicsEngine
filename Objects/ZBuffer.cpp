#include <iostream>
#include "ZBuffer.h"
#include "../Include/easy_image.h"
#include "fstream"

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

void ZBuffer::render(const std::string &filename) {
    img::EasyImage img((*this)[0].size(), size());
    for (int y = 0; y < size(); y++) {
        for (int x = 0; x < (*this)[0].size(); x++) {
            double val = (*this)[y][x];
            double absVal = 1/std::abs(val);
            img::Color c = (val==std::numeric_limits<double>::infinity()) ? img::Color(0,0,0) : img::Color(255*absVal,255*absVal,255*absVal);
            img(x,y) = c;
        }
    }
    std::ofstream f_out(filename.c_str(),std::ios::trunc | std::ios::out | std::ios::binary);
    f_out << img;
}

void ZBuffer::print() {
    for (int y = 0; y < size(); y++) {
        for (int x = 0; x < (*this)[0].size(); x++) {
            double val = (*this)[y][x];
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}
