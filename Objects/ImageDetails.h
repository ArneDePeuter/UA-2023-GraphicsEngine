#ifndef ENGINE_IMAGEDETAILS_H
#define ENGINE_IMAGEDETAILS_H

#include "Line2D.h"

class ImageDetails {
public:
    ImageDetails(double d, double dx, double dy, double imageX, double imageY);
    static ImageDetails calculateDetails(const Lines2D &lines2D, const int &size);

    double d, dx, dy, imageX, imageY;
};


#endif //ENGINE_IMAGEDETAILS_H
