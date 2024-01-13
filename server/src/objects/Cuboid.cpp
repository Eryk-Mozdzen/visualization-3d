#include "Cuboid.h"

namespace gs {

Cuboid::Cuboid(ArgumentStream &stream) : Object(stream) {

    Qt3DExtras::QCuboidMesh *mesh = new Qt3DExtras::QCuboidMesh();

    entity->addComponent(mesh);
}

}
