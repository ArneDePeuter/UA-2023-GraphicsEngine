#include "IniLoader.h"
#include "Renderer.h"

img::EasyImage IniLoader::createImage(const ini::Configuration &configuration) {
    img::Color backgroundcolor;
    int size;
    bool zBuffering;
    std::pair<Lines2D,std::vector<Triangle>> p = parse(configuration, backgroundcolor, size, zBuffering);
    Lines2D lines = p.first;
    std::vector<Triangle> triangles = p.second;
    if (triangles.empty()) {
        return Renderer::draw2DLines(backgroundcolor, lines, size, zBuffering);
    } else {
        return Renderer::drawZBufTriangles(backgroundcolor, triangles, lines, size);
    }
}

std::pair<Lines2D, std::vector<Triangle>> IniLoader::parse(const ini::Configuration &configuration, img::Color &backgroundcolor, int &size, bool &zBuffering) {
    size = configuration["General"]["size"].as_int_or_die();

    ini::DoubleTuple colorTuple = configuration["General"]["backgroundcolor"].as_double_tuple_or_die();
    backgroundcolor = img::Color(colorTuple[0]*255, colorTuple[1]*255, colorTuple[2]*255);

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

    zBuffering = false;
    if (type == "2DLSystem") {
        LSystem2D lSys = IniLoader::loadLSystem2D(configuration);
        return {lSys.lines,{}};
    } else if (type == "Wireframe" || type == "ZBufferedWireframe") {
        if (type == "ZBufferedWireframe") zBuffering = true;
        Wireframe wf = IniLoader::loadWireFrame(configuration,clipping, viewDirection, dNear, dFar,hfov,aspectRatio);
        return {wf.project(1),{}};
    }else if (type == "ZBuffering") {
        Scene s = IniLoader::loadScene(configuration,clipping, viewDirection, dNear, dFar,hfov,aspectRatio);
        zBuffering=true;
        return {s.project(1),s.getTriangles()};
    }
    return {{},{}};
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

    ini::DoubleTuple colorTuple = section["color"].as_double_tuple_or_die();
    obj.color = img::Color(colorTuple[0]*255, colorTuple[1]*255, colorTuple[2]*255);

    obj.applyTransformation(Calculator::superMatrix(scale, rotateX, rotateY, rotateZ, obj.center));
    return obj;
}



