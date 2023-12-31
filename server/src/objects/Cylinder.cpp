#include "Cylinder.h"

namespace gs {

Cylinder::Cylinder(Qt3DCore::QEntity *root) : Object(root) {

    Qt3DExtras::QCylinderMesh *mesh = new Qt3DExtras::QCylinderMesh();
    mesh->setRadius(1.0f);
    mesh->setLength(1.0f);
    mesh->setRings(100);
    mesh->setSlices(100);

    entity->addComponent(mesh);
}

}
