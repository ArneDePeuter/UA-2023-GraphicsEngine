#include "IniLoader.h"
#include "Renderer.h"
#include "Light.h"

img::EasyImage IniLoader::createImage(const ini::Configuration &configuration) {
    return parse(configuration);
}

img::EasyImage IniLoader::parse(const ini::Configuration &configuration) {
    int size = configuration["General"]["size"].as_int_or_die();

    ini::DoubleTuple colorTuple = configuration["General"]["backgroundcolor"].as_double_tuple_or_die();
    img::Color backgroundcolor = img::Color(colorTuple[0]*255, colorTuple[1]*255, colorTuple[2]*255);

    std::string type = configuration["General"]["type"].as_string_or_die();

    bool clipping = configuration["General"]["clipping"].as_bool_or_default(false);
    ini::DoubleTuple viewDirection;
    int dNear,dFar, hfov;
    double aspectRatio;
    if (clipping) {
        viewDirection = configuration["General"]["viewDirection"].as_double_tuple_or_die();
        dNear = configuration["General"]["dNear"].as_int_or_die();
        dFar = configuration["General"]["dFar"].as_int_or_die();
        hfov = configuration["General"]["hfov"].as_int_or_die();
        aspectRatio = configuration["General"]["aspectRatio"].as_double_or_die();
    }

    if (type == "2DLSystem") {
        LSystem2D lSys = IniLoader::loadLSystem2D(configuration);
        return Renderer::draw2DLines(backgroundcolor, lSys.lines, size, false);
    } else if (type == "Wireframe" || type == "ZBufferedWireframe") {
        bool zBuf = false;
        if (type == "ZBufferedWireframe") zBuf = true;
        Wireframe wf = IniLoader::loadWireFrame(configuration,clipping, viewDirection, dNear, dFar,hfov,aspectRatio);
        return Renderer::draw2DLines(backgroundcolor, wf.project(1), size, zBuf);
    } else if (type == "ZBuffering") {
        Scene s = IniLoader::loadScene(configuration,clipping, viewDirection, dNear, dFar,hfov,aspectRatio);
        return Renderer::drawZBufTriangles(backgroundcolor, s.getTriangles(), s.project(1), size, s.lights);
    } else if (type == "LightedZBuffering") {
        Scene s = IniLoader::loadSceneWLights(configuration,clipping, viewDirection, dNear, dFar,hfov,aspectRatio);
        return Renderer::drawZBufTriangles(backgroundcolor, s.getTriangles(), s.project(1), size, s.lights);
    }
    return img::EasyImage();
}

LSystem2D IniLoader::loadLSystem2D(const ini::Configuration &configuration) {
    std::string inputfile = configuration["2DLSystem"]["inputfile"].as_string_or_die();

    ini::DoubleTuple colorTuple = configuration["2DLSystem"]["color"].as_double_tuple_or_die();
    img::Color color = img::Color(colorTuple[0]*255, colorTuple[1]*255, colorTuple[2]*255);

    return LSystem2D(inputfile, color);
}

Wireframe IniLoader::loadWireFrame(const ini::Configuration &configuration, const bool &clipping_, const ini::DoubleTuple &viewDirection_,
                                   const int &dNear_, const int &dFar_, const int &hfov_, const double &aspectRatio_) {
    Wireframe wf;

    ini::Section general = configuration["General"];
    wf.camera = Camera(general["eye"], clipping_, viewDirection_, dNear_, dFar_, hfov_, aspectRatio_);
    int nrFigures = general["nrFigures"];

    for (int i = 0; i < nrFigures; i++) {
        ini::Section section = configuration["Figure" + std::to_string(i)];
        Object3D object = loadObject3D(section);
        wf.objects3D.push_back(object);
    }

    wf.camera.eyePointTransform(wf.objects3D);
    return wf;
}

Scene IniLoader::loadScene(const ini::Configuration &configuration, const bool &clipping_, const ini::DoubleTuple &viewDirection_,
                           const int &dNear_, const int &dFar_, const int &hfov_, const double &aspectRatio_) {
    Scene scene;

    ini::Section general = configuration["General"];
    scene.camera = Camera(general["eye"], clipping_, viewDirection_, dNear_, dFar_, hfov_, aspectRatio_);
    int nrFigures = general["nrFigures"];

    for (int i = 0; i < nrFigures; i++) {
        ini::Section section = configuration["Figure" + std::to_string(i)];
        scene.objects3D.push_back(loadObject3D(section));
    }
    scene.triangulate();
    scene.camera.eyePointTransform(scene.objects3D);
    return scene;
}

Object3D IniLoader::loadObject3D(const ini::Section &section) {
    Object3D obj;
    std::string type = section["type"];
    if (type == "LineDrawing") {
        obj = Object3D::createLineDrawing(section);
    }
    else if (type == "Cube") {
        obj = Object3D::createCube();
    }
    else if (type == "Tetrahedron") {
        obj = Object3D::createTetrahedron();
    }
    else if (type == "Octahedron") {
        obj = Object3D::createOctahedron();
    }
    else if (type == "Icosahedron") {
        obj = Object3D::createIcosahedron();
    }
    else if (type == "Dodecahedron") {
        obj = Object3D::createDodecahedron();
    }
    else if (type == "Sphere") {
        obj = Object3D::createSphere(section["n"].as_int_or_die());
    }
    else if (type == "Cylinder") {
        obj = Object3D::createCylinder(section["n"].as_int_or_die(),section["height"].as_double_or_die());
    }
    else if (type == "Cone") {
        obj = Object3D::createCone(section["n"].as_int_or_die(),section["height"].as_double_or_die());
    }
    else if (type == "Torus") {
        obj = Object3D::createTorus(section["r"].as_double_or_die(), section["R"].as_double_or_die(), section["n"].as_int_or_die(), section["m"].as_int_or_die());
    }
    else if (type == "ObjFile") {
        obj = Object3D::loadObj(section["file"].as_string_or_die());
    }
    else if (type == "3DLSystem") {
        obj = LSystem3D(section["inputfile"].as_string_or_die());
    }
    else if (type == "BuckyBall") {
        obj = Object3D::createBuckyBall();
    }
    else {
        int nrIterations = section["nrIterations"].as_int_or_die();
        if (type == "MengerSponge") {
            obj = Object3D::createMenger(nrIterations);
        }
        else
        {
            int fractalScale = section["fractalScale"].as_int_or_die();
            if (type == "FractalCube") {
                obj = Object3D::createFractalCube(fractalScale, nrIterations);
            }
            else if (type == "FractalTetrahedron") {
                obj = Object3D::createFractalTetrahedron(fractalScale, nrIterations);
            }
            else if (type == "FractalIcosahedron") {
                obj = Object3D::createFractalIcosahedron(fractalScale, nrIterations);
            }
            else if (type == "FractalDodecahedron") {
                obj = Object3D::createFractalDodecahedron(fractalScale, nrIterations);
            }
            else if (type == "FractalOctahedron") {
                obj = Object3D::createFractalOctahedron(fractalScale, nrIterations);
            }
        }
    }

    int rotateX = section["rotateX"].as_double_or_die();
    int rotateY = section["rotateY"].as_double_or_die();
    int rotateZ = section["rotateZ"].as_double_or_die();
    double scale = section["scale"].as_double_or_die();

    ini::DoubleTuple centertuple = section["center"].as_double_tuple_or_die();
    obj.center = Vector3D::point(centertuple[0], centertuple[1], centertuple[2]);

    ini::DoubleTuple colorTuple;

    if (section["color"].as_double_tuple_if_exists(colorTuple)) {
        obj.color = img::Color(colorTuple[0]*255, colorTuple[1]*255, colorTuple[2]*255);
    } else {
        obj.ambientReflection = section["ambientReflection"].as_double_tuple_or_die();
        obj.diffuseReflection = section["diffuseReflection"].as_double_tuple_or_default({1,1,1});
    }

    obj.applyTransformation(Calculator::superMatrix(scale, rotateX, rotateY, rotateZ, obj.center));
    return obj;
}

Scene IniLoader::loadSceneWLights(const ini::Configuration &configuration, const bool &clipping_,
                                  const ini::DoubleTuple &viewDirection_, const int &dNear_, const int &dFar_,
                                  const int &hfov_, const double &aspectRatio_) {
    Scene s = loadScene(configuration, clipping_, viewDirection_, dNear_, dFar_, hfov_, aspectRatio_);
    int nrLights = configuration["General"]["nrLights"].as_int_or_die();
    for (int i = 0; i < nrLights; i++) {
        ini::Section section = configuration["Light" + std::to_string(i)];

        ini::DoubleTuple ambientLight = section["ambientLight"].as_double_tuple_or_die();

        ini::DoubleTuple diffuseLight;
        bool hasDiffuse = section["diffuseLight"].as_double_tuple_if_exists(diffuseLight);

        bool infinity;
        bool hasInfinity = section["infinity"].as_bool_if_exists(infinity);

        ini::DoubleTuple directionTuple;
        bool hasDirection = section["direction"].as_double_tuple_if_exists(directionTuple);

        if (hasInfinity) {
            if (infinity && hasDirection) {
                InfLight *infL = new InfLight();
                infL->ambientLight = ambientLight;
                infL->diffuseLight = diffuseLight;

                Vector3D dir;
                dir.x = directionTuple[0];
                dir.y = directionTuple[1];
                dir.z = directionTuple[2];
                infL->ldVector = Vector3D::normalise(dir);

                s.lights.push_back(infL);
            }
        } else {
            AmbientLight *l = new AmbientLight();
            l->ambientLight = ambientLight;
            s.lights.push_back(l);
        }
    }
    return s;
}



