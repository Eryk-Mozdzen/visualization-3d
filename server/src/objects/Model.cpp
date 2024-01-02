#include "Model.h"

namespace gs {

Model::Model(Qt3DCore::QEntity *root, QTextStream &stream) : Object(root, stream) {

    QString attribute;
    stream >> attribute;

    if(attribute!="path") {
        qDebug() << "model need path to mesh file, attribute:" << attribute;
        return;
    }

    QString path;
    stream >> path;

    if(path.isEmpty()) {
        qDebug() << "model path empty";
        return;
    }

    Qt3DRender::QMesh *mesh = new Qt3DRender::QMesh();
    mesh->setSource(QUrl::fromLocalFile(path));

    entity->addComponent(mesh);
}

}
