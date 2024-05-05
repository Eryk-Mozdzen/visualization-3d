#include "Sphere.h"

namespace gs {

Sphere::Sphere(ArgumentStream &stream) : Object(stream) {

    Qt3DExtras::QSphereMesh *mesh = new Qt3DExtras::QSphereMesh();
	mesh->setRings(100);
    mesh->setSlices(100);
    mesh->setGenerateTangents(true);

    if(stream.fetch("geometry")) {
        float radius;
        stream >> radius;

        mesh->setRadius(radius);
    }

    entity->addComponent(mesh);
}

}
