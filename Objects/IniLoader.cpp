#include "IniLoader.h"
#include "Renderer.h"
#include "Light.h"

img::EasyImage IniLoader::createImage(const ini::Configuration &configuration) {
    return parse(configuration);
}

img::EasyImage IniLoader::parse(const ini::Configuration &configuration) {
    int size = configuration["General"]["size"].as_int_or_die();

    img::Color backgroundcolor = configuration["General"]["backgroundcolor"].as_double_tuple_or_die();

    ClippingSettings settings = loadClippingSettings(configuration);

    std::string type = configuration["General"]["type"].as_string_or_die();
    if (type == "2DLSystem") {
        LSystem2D lSys = IniLoader::loadLSystem2D(configuration);
        return Renderer::draw2DLines(backgroundcolor, lSys.lines, size, false);
    } else if (type == "Wireframe" || type == "ZBufferedWireframe") {
        Scene s = IniLoader::loadScene(configuration, settings, false, false);
        return Renderer::draw2DLines(backgroundcolor, s.project(1), size, (type == "ZBufferedWireframe"));
    } else if (type == "ZBuffering") {
        Scene s = IniLoader::loadScene(configuration, settings, true, false);
        return Renderer::drawZBufTriangles(s, backgroundcolor, size);
    } else if (type == "LightedZBuffering") {
        Scene s = IniLoader::loadScene(configuration, settings, true, true);
        return Renderer::drawZBufTriangles(s, backgroundcolor, size);
    }
    return img::EasyImage();
}

LSystem2D IniLoader::loadLSystem2D(const ini::Configuration &configuration) {
    std::string inputfile = configuration["2DLSystem"]["inputfile"].as_string_or_die();
    img::Color color = configuration["2DLSystem"]["color"].as_double_tuple_or_die();
    return LSystem2D(inputfile, color);
}

ClippingSettings IniLoader::loadClippingSettings(const ini::Configuration &configuration) {
    if (configuration["General"]["clipping"].as_bool_or_default(false)) {
        return ClippingSettings(
                true,
                configuration["General"]["viewDirection"].as_double_tuple_or_die(),
                configuration["General"]["dNear"].as_int_or_die(),
                configuration["General"]["dFar"].as_int_or_die(),
                configuration["General"]["hfov"].as_int_or_die(),
                configuration["General"]["aspectRatio"].as_double_or_die()
        );
    }
    return ClippingSettings(false, {0,0,0}, 0, 0, 0, 0);
}

Scene IniLoader::loadScene(const ini::Configuration &configuration, const ClippingSettings &settings, const bool &doTriangulate, const bool &lights) {
    ini::Section general = configuration["General"];
    Camera camera = Camera(general["eye"], settings);
    int nrFigures = general["nrFigures"];

    Objects3D objects;
    for (int i = 0; i < nrFigures; i++) {
        ini::Section section = configuration["Figure" + std::to_string(i)];
        objects.push_back(loadObject3D(section));
    }

    std::vector<Light*> lightsVec;
    if (lights) {
        bool shadows;
        bool hasShadowBool = general["shadowEnabled"].as_bool_if_exists(shadows);
        if (!hasShadowBool || !shadows) {
            lightsVec = loadLights(configuration, camera);
        } else {
            int shadowMask = general["shadowMask"].as_int_or_die();
            lightsVec = loadLights(configuration, camera, shadowMask);
        }
    } else {
        lightsVec.push_back(new AmbientLight({1,1,1}));
    }
    return Scene(objects, camera, lightsVec, doTriangulate);
}

Object3D IniLoader::loadObject3D(const ini::Section &section) {
    std::string type = section["type"];
    Object3D obj = Object3D::Object3DFactory::load(type, section);

    int rotateX = section["rotateX"].as_double_or_die();
    int rotateY = section["rotateY"].as_double_or_die();
    int rotateZ = section["rotateZ"].as_double_or_die();
    double scale = section["scale"].as_double_or_die();

    ini::DoubleTuple centertuple = section["center"].as_double_tuple_or_die();
    obj.center = Vector3D::point(centertuple[0], centertuple[1], centertuple[2]);

    ini::DoubleTuple colorTuple;

    if (section["color"].as_double_tuple_if_exists(colorTuple)) {
        obj.color = colorTuple;
        obj.ambientReflection = colorTuple;
    } else {
        obj.ambientReflection = section["ambientReflection"].as_double_tuple_or_die();
        obj.diffuseReflection = section["diffuseReflection"].as_double_tuple_or_default({1,1,1});
        obj.specularReflection = section["specularReflection"].as_double_tuple_or_default({0,0,0});
        obj.reflectionCoefficient = section["reflectionCoefficient"].as_double_or_default(0);
    }

    obj.applyTransformation(Calculator::superMatrix(scale, rotateX, rotateY, rotateZ, obj.center));
    return obj;
}

std::vector<Light *> IniLoader::loadLights(const ini::Configuration &configuration, const Camera &cam,  const int &shadowMask) {
    std::vector<Light *> lights;
    int nrLights = configuration["General"]["nrLights"].as_int_or_die();
    for (int i = 0; i < nrLights; i++) {
        ini::Section section = configuration["Light" + std::to_string(i)];

        ini::DoubleTuple ambientLight = section["ambientLight"].as_double_tuple_or_die();

        bool infinity;
        bool hasInfinity = section["infinity"].as_bool_if_exists(infinity);

        if (!hasInfinity) {
            lights.push_back(new AmbientLight(ambientLight));
            continue;
        }

        ini::DoubleTuple diffuseLight = section["diffuseLight"].as_double_tuple_or_die();
        ini::DoubleTuple specularLight = section["specularLight"].as_double_tuple_or_default({0,0,0});

        if (infinity) {
            ini::DoubleTuple dir = section["direction"].as_double_tuple_or_die();
            Vector3D ldVector = Vector3D::vector(dir[0], dir[1], dir[2]);
            lights.push_back(new InfLight(ambientLight, diffuseLight, specularLight, ldVector));
        }
        else {
            ini::DoubleTuple loc = section["location"].as_double_tuple_or_die();
            Vector3D location = Vector3D::point(loc[0], loc[1], loc[2]);
            double spotAngle = section["spotAngle"].as_double_or_default(-1);
            if (shadowMask!=0) {
                lights.push_back(new ShadowPointLight(ambientLight, diffuseLight, specularLight,location, spotAngle, shadowMask, cam.eyeMatrix));
            } else {
                lights.push_back(new PointLight(ambientLight, diffuseLight, specularLight, location, spotAngle));
            }
        }
    }
    return lights;
}




