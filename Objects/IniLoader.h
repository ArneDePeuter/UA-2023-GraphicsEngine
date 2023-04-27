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
    static img::EasyImage parse(const ini::Configuration &configuration);
    static LSystem2D loadLSystem2D(const ini::Configuration &configuration);
    static Object3D loadObject3D(const ini::Section &section);
    static Wireframe loadWireFrame(const ini::Configuration &configuration, const bool &clipping_, const ini::DoubleTuple &viewDirection_,
                                   const int &dNear_, const int &dFar_, const int &hfov_, const double &aspectRatio_);
    static Scene loadScene(const ini::Configuration &configuration, const bool &clipping_, const ini::DoubleTuple &viewDirection_,
                           const int &dNear_, const int &dFar_, const int &hfov_, const double &aspectRatio_);
    static Scene loadSceneWLights(const ini::Configuration &configuration, const bool &clipping_, const ini::DoubleTuple &viewDirection_,
                           const int &dNear_, const int &dFar_, const int &hfov_, const double &aspectRatio_);
};

#endif //ENGINE_INILOADER_H
