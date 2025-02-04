#include "primitives/Sphere.h"

namespace primitives {

Sphere::Sphere(const QJsonObject json) : Object{json} {
    Qt3DExtras::QSphereMesh *mesh = new Qt3DExtras::QSphereMesh();
	mesh->setRings(100);
    mesh->setSlices(100);
    mesh->setGenerateTangents(true);

    if(json.contains("geometry")) {
        const QJsonObject geometry = json["geometry"].toObject();

        if(geometry.contains("radius")) {
            const double radius = geometry["radius"].toDouble();

            mesh->setRadius(radius);
        } else {
            mesh->setRadius(1);
        }
    }

    entity->addComponent(mesh);
}

}
