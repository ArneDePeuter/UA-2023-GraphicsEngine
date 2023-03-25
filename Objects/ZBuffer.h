#ifndef ENGINE_ZBUFFER_H
#define ENGINE_ZBUFFER_H

#include "vector"
#include "limits"

class ZBuffer : public std::vector<std::vector<double>>{
public:
    ZBuffer(const int &width, const int &heigth);
    static double calculateVal(const double &zA, const double &zB, const int &a, const int &i);
    bool apply(const int &x, const int &y, const double &zA, const double &zB, const int &a, int &i);
};


#endif //ENGINE_ZBUFFER_H
