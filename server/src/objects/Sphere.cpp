#include "Sphere.h"

namespace gs {

Sphere::Sphere(Qt3DCore::QEntity *root, QTextStream &stream) : Object(root, stream) {

    Qt3DExtras::QSphereMesh *mesh = new Qt3DExtras::QSphereMesh();
    mesh->setRadius(1);
	mesh->setRings(100);
    mesh->setSlices(100);
    mesh->setGenerateTangents(true);

    entity->addComponent(mesh);
}

}
