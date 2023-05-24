#ifndef ENGINE_ZBUFFER_H
#define ENGINE_ZBUFFER_H

#include "vector"
#include "limits"

class ZBuffer : public std::vector<std::vector<double>>{
public:
    ZBuffer(const int &width, const int &heigth);
    static double calculateVal(const double &zA, const double &zB, const unsigned int &a, const unsigned int &i);
    bool apply(const unsigned int &x, const unsigned int &y, const double &zA, const double &zB, const unsigned int &a, int unsigned &i);
    bool apply(const unsigned int &x, const unsigned int &y, const double &bufVal);
    void render(const std::string &filename);
    void print();
};


#endif //ENGINE_ZBUFFER_H
