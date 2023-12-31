#include "Model.h"

namespace gs {

Model::Model(Qt3DCore::QEntity *root, const QString path) : Object(root) {

    Qt3DRender::QMesh *mesh = new Qt3DRender::QMesh();
    mesh->setSource(QUrl::fromLocalFile(path));

    entity->addComponent(mesh);
}

}
