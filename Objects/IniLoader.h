#ifndef ENGINE_INILOADER_H
#define ENGINE_INILOADER_H

#include "Object3D.h"
#include "Wireframe.h"
#include "LSystem2D.h"
#include "Camera.h"
#include "../Include/ini_configuration.h"
#include "LSystem3D.h"
#include "Scene.h"

class IniLoader {
public:
    static img::EasyImage createImage(const ini::Configuration &configuration);
    static std::pair<Lines2D,std::vector<Triangle>> parse(const ini::Configuration &configuration, img::Color &backgroundcolor, int &size, bool &zBuffering);
    static LSystem2D loadLSystem2D(const ini::Configuration &configuration);
    static Wireframe loadWireFrame(const ini::Configuration &configuration);
    static Object3D loadObject3D(const ini::Section &section);
    static Scene loadScene(const ini::Configuration &configuration);
};

#endif //ENGINE_INILOADER_H
