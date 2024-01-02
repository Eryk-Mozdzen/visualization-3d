#include "Cuboid.h"

namespace gs {

Cuboid::Cuboid(Qt3DCore::QEntity *root, QTextStream &stream) : Object(root, stream) {

    Qt3DExtras::QCuboidMesh *mesh = new Qt3DExtras::QCuboidMesh();

    entity->addComponent(mesh);
}

}
