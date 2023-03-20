#include "IniLoader.h"

LSystem2D IniLoader::loadLSystem2D(const ini::Configuration &configuration, int &size, img::Color &backgroundcolor) {
    size = configuration["General"]["size"].as_int_or_die();

    ini::DoubleTuple colorTuple = configuration["General"]["backgroundcolor"].as_double_tuple_or_die();
    backgroundcolor = img::Color(colorTuple[0]*255, colorTuple[1]*255, colorTuple[2]*255);

    std::string inputfile = configuration["2DLSystem"]["inputfile"].as_string_or_die();

    colorTuple = configuration["2DLSystem"]["color"].as_double_tuple_or_die();

    img::Color color = img::Color(colorTuple[0]*255, colorTuple[1]*255, colorTuple[2]*255);

    return LSystem2D(inputfile, color);
}

Wireframe IniLoader::loadWireFrame(const ini::Configuration &configuration, int &size, img::Color &backgroundcolor) {
    Wireframe wf;

    ini::Section general = configuration["General"];
    size = general["size"].as_int_or_die();
    ini::DoubleTuple colorTuple = general["backgroundcolor"].as_double_tuple_or_die();
    backgroundcolor = img::Color(colorTuple[0]*255, colorTuple[1]*255, colorTuple[2]*255);
    wf.camera = Camera(general["eye"]);

    int nrFigures = general["nrFigures"];

    for (int i = 0; i < nrFigures; i++) {
        ini::Section section = configuration["Figure" + std::to_string(i)];
        Object3D object = loadObject3D(section);
        wf.objects3D.push_back(object);
    }

    wf.camera.eyePointTransform(wf.objects3D);
    return wf;
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
    } else if (type == "3DLSystem") {
        obj = LSystem3D(section["inputfile"].as_string_or_die());
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

