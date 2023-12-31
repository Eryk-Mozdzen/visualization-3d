#include "Cuboid.h"

namespace gs {

Cuboid::Cuboid(Qt3DCore::QEntity *root) : Object(root) {

    Qt3DExtras::QCuboidMesh *mesh = new Qt3DExtras::QCuboidMesh();

    entity->addComponent(mesh);
}

}
