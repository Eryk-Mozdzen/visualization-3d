#include "primitives/Model.h"

namespace primitives {

Model::Model(const QJsonObject json) : Object{json} {
    Qt3DRender::QMesh *mesh = new Qt3DRender::QMesh();

    if(json.contains("geometry")) {
        const QJsonObject geometry = json["geometry"].toObject();

        if(geometry.contains("file")) {
            const QString file = geometry["file"].toString();

            mesh->setSource(QUrl::fromLocalFile(file));
        }
    }

    entity->addComponent(mesh);
}

}
