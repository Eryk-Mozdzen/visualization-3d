#include "Model.h"

namespace gs {

Model::Model(ArgumentStream &stream) : Object(stream) {

    Qt3DRender::QMesh *mesh = new Qt3DRender::QMesh();

    if(stream.fetch("path")) {
        QString path;
        stream >> path;

        mesh->setSource(QUrl::fromLocalFile(path));

    } else {
        qDebug() << "model need path to mesh file";
        return;
    }

    entity->addComponent(mesh);
}

}
