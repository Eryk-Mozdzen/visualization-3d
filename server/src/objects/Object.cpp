#include "Object.h"

namespace gs {

Object::Object(Qt3DCore::QEntity *root, QTextStream &stream) : parent{nullptr} {
    entity = new Qt3DCore::QEntity(root);

    material = new Material();
    transformGlobal = new Transform();
    transformLocal = new Transform();

    entity->addComponent(material);
    entity->addComponent(transformGlobal);

    while(!stream.atEnd()) {
        const QString line = stream.readAll();
        QList<QString> words = line.split(' ');
        words.removeAll(QString());
        const QString first = words.first();

        stream << line;

        if(first!="transform" && first!="material") {
            break;
        }

        QString attribute;
        stream >> attribute;

        if(attribute=="transform") {
            stream >> *transformLocal;
            update();
        } else if(attribute=="material") {
            stream >> *material;
        }
    }
}

Object::~Object() {
    for(Object *child : childs) {
        delete child;
    }

    entity->deleteLater();
}

void Object::addChild(const QString name, Object *child) {
    child->parent = this;
    childs[name] = child;
}

Object * Object::getChild(const QString name) {
    if(!childs.contains(name)) {
        return nullptr;
    }

    return childs.value(name);
}

void Object::update() {
    if(parent!=nullptr) {
        transformGlobal->setMatrix(parent->transformGlobal->matrix()*transformLocal->matrix());
    } else {
        transformGlobal->setMatrix(transformLocal->matrix());
    }

    for(Object *child : childs) {
        child->update();
    }
}

Material * Object::getMaterial() const {
    return material;
}

Transform * Object::getTransformGlobal() const {
    return transformGlobal;
}

Transform * Object::getTransformLocal() const {
    return transformLocal;
}

QTextStream & operator>>(QTextStream &stream, Object &object) {

    while(!stream.atEnd()) {
        const QString line = stream.readAll();
        QList<QString> words = line.split(' ');
        words.removeAll(QString());
        const QString first = words.first();

        stream << line;

        if(first!="transform" && first!="material") {
            break;
        }

        QString attribute;
        stream >> attribute;

        if(attribute=="transform") {
            stream >> *object.transformLocal;
            object.update();
        } else if(attribute=="material") {
            stream >> *object.material;
        }
    }

    return stream;
}

}
