#ifndef ENGINE_INILOADER_H
#define ENGINE_INILOADER_H

#include "Object3D.h"
#include "LSystem2D.h"
#include "Camera.h"
#include "../Include/ini_configuration.h"
#include "LSystem3D.h"
#include "Scene.h"
#include "ClippingSettings.h"

class IniLoader {
public:
    static img::EasyImage createImage(const ini::Configuration &configuration);
    static img::EasyImage parse(const ini::Configuration &configuration);
    static LSystem2D loadLSystem2D(const ini::Configuration &configuration);
    static ClippingSettings loadClippingSettings(const ini::Configuration &configuration);
    static Object3D loadObject3D(const ini::Section &section);
    static Scene loadScene(const ini::Configuration &configuration, const ClippingSettings &settings, const bool &doTriangulate, const bool &lights);
    static std::vector<Light*> loadLights(const ini::Configuration &configuration, const Camera &cam, const int &shadowMask=0);
};

#endif //ENGINE_INILOADER_H
