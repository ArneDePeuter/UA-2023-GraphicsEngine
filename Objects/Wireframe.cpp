#include "Face.h"
#include "Wireframe.h"
#include "Object3D.h"

Wireframe::Wireframe(ini::Configuration &config) {
    ini::Section general = config["General"];
    size = general["size"].as_int_or_die();
    ini::DoubleTuple colorTuple = general["backgroundcolor"].as_double_tuple_or_die();
    backgroundColor = img::Color(colorTuple[0]*255, colorTuple[1]*255, colorTuple[2]*255);
    camera = Camera(general["eye"]);

    int nrFigures = general["nrFigures"];

    for (int i = 0; i < nrFigures; i++) {
        ini::Section objSec = config["Figure" + std::to_string(i)];
        Object3D object = Object3D(objSec);
        objects3D.push_back(object);
    }

    camera.eyePointTransform(objects3D);
}

Lines2D Wireframe::project(const double d) {
    Lines2D lines;

    for (Object3D obj : objects3D) {
        for (Face f : obj.faces) {
            Vector3D p1 = obj.vertexes[f.point_indexes[0]];
            Vector3D p2 = obj.vertexes[f.point_indexes[1]];

            Line2D newLine(point3dto2d(p1,d), point3dto2d(p2, d), obj.color);
            lines.push_back(newLine);
        }
    }
    return lines;
}

Point2D Wireframe::point3dto2d(Vector3D &point, const double d) {
    Point2D p;
    p.x = (d*point.x)/-point.z;
    p.y = (d*point.y)/-point.z;
    return p;
}