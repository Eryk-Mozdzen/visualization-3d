#include "Cuboid.h"

namespace gs {

Cuboid::Cuboid(ArgumentStream &stream) : Object(stream) {

    Qt3DExtras::QCuboidMesh *mesh = new Qt3DExtras::QCuboidMesh();

    if(stream.fetch("geometry")) {
        float x, y, z;
        stream >> x >> y >> z;

        mesh->setXExtent(x);
        mesh->setYExtent(y);
        mesh->setZExtent(z);
    }

    entity->addComponent(mesh);
}

}
