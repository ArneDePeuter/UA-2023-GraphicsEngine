#ifndef ENGINE_INILOADER_H
#define ENGINE_INILOADER_H

#include "Object3D.h"
#include "Wireframe.h"
#include "LSystem2D.h"
#include "Camera.h"
#include "../Include/ini_configuration.h"

class IniLoader {
public:
    static LSystem2D loadLSystem2D(const ini::Configuration &configuration, int &size, img::Color &backgroundcolor);
    static Wireframe loadWireFrame(const ini::Configuration &configuration, int &size, img::Color &backgroundcolor);
    static Object3D loadObject3D(const ini::Section &section);
};

#endif //ENGINE_INILOADER_H
