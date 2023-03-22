#include "Face.h"
#include "Wireframe.h"
#include "Object3D.h"

Wireframe::Wireframe() {}

Lines2D Wireframe::project(const double d) {
    Lines2D lines;
    for (Object3D obj : objects3D) {
        for (Face f : obj.faces) {
            for (int i = 0; i < f.point_indexes.size()-1; i++) {
                Vector3D p1 = obj.vertexes[f.point_indexes[i]];
                Vector3D p2 = obj.vertexes[f.point_indexes[i+1]];

                Line2D newLine(point3dto2d(p1,d), point3dto2d(p2, d), obj.color);
                lines.push_back(newLine);
            }
            Vector3D p1 = obj.vertexes[f.point_indexes[0]];
            Vector3D p2 = obj.vertexes[f.point_indexes[f.point_indexes.size()-1]];
            Line2D newLine(point3dto2d(p1,d), point3dto2d(p2, d), obj.color);
            lines.push_back(newLine);
        }
    }
    return lines;
}

Point2D Wireframe::point3dto2d(Vector3D &point, const double d) {
    Point2D p((d*point.x)/-point.z, (d*point.y)/-point.z, point.z);
    return p;
}