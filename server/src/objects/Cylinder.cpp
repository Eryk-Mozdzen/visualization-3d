#include "Cylinder.h"

namespace gs {

Cylinder::Cylinder(ArgumentStream &stream) : Object(stream) {

    Qt3DExtras::QCylinderMesh *mesh = new Qt3DExtras::QCylinderMesh();
    mesh->setRings(100);
    mesh->setSlices(100);

    if(stream.fetch("geometry")) {
        float radius, height;
        stream >> radius >> height;

        mesh->setRadius(radius);
        mesh->setLength(height);
    }

    entity->addComponent(mesh);
}

}
