#include "primitives/Model.h"

namespace primitives {

Model::Model(utils::ArgumentStream &stream) : Object{stream} {
    Qt3DRender::QMesh *mesh = new Qt3DRender::QMesh();

    if(stream.fetch("geometry")) {
        QString path;
        stream >> path;

        mesh->setSource(QUrl::fromLocalFile(path));
    }

    entity->addComponent(mesh);
}

}
