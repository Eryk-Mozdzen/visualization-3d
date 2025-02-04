#include "primitives/Cuboid.h"

namespace primitives {

Cuboid::Cuboid(const QJsonObject json) : Object{json} {
    Qt3DExtras::QCuboidMesh *mesh = new Qt3DExtras::QCuboidMesh();

    if(json.contains("geometry")) {
        const QJsonObject geometry = json["geometry"].toObject();

        if(geometry.contains("size")) {
            const QJsonArray size = geometry["size"].toArray();

            if(size.size()==3) {
                mesh->setXExtent(size[0].toDouble());
                mesh->setYExtent(size[1].toDouble());
                mesh->setZExtent(size[2].toDouble());
            } else {
                mesh->setXExtent(1);
                mesh->setYExtent(1);
                mesh->setZExtent(1);
            }
        }
    }

    entity->addComponent(mesh);
}

}
