#ifndef ENGINE_CLIPPINGSETTINGS_H
#define ENGINE_CLIPPINGSETTINGS_H

#include "../Include/ini_configuration.h"

class ClippingSettings {
public:
    ClippingSettings(const bool &clipping, const ini::DoubleTuple &viewDirection, const int &dNear, const int &dFar, const int &hfov, const double &aspectRatio)
    : clipping(clipping), viewDirection(viewDirection), dNear(dNear), dFar(dFar), hfov(hfov), aspectRatio(aspectRatio) {};

    bool clipping;
    ini::DoubleTuple viewDirection;
    int dNear;
    int dFar;
    int hfov;
    double aspectRatio;
};


#endif //ENGINE_CLIPPINGSETTINGS_H
