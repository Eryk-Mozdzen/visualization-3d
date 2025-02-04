#include "primitives/Cylinder.h"

namespace primitives {

Cylinder::Cylinder(const QJsonObject json) : Object{json} {
    Qt3DExtras::QCylinderMesh *mesh = new Qt3DExtras::QCylinderMesh();
    mesh->setRings(100);
    mesh->setSlices(100);

    if(json.contains("geometry")) {
        const QJsonObject geometry = json["geometry"].toObject();

        if(geometry.contains("radius") && geometry.contains("height")) {
            const double radius = geometry["radius"].toDouble();
            const double height = geometry["height"].toDouble();

            mesh->setRadius(radius);
            mesh->setLength(height);
        } else {
            mesh->setRadius(1);
            mesh->setLength(1);
        }
    }

    entity->addComponent(mesh);
}

}
