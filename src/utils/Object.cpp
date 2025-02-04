#include <Qt3DExtras>
#include <Qt3DRender>
#include <QJsonObject>

#include "Object.h"
#include "utils/Material.h"
#include "utils/Transform.h"

namespace utils {

Qt3DCore::QEntity *Object::root = new Qt3DCore::QEntity();

Object::Object(const QJsonObject json) : parent{nullptr} {
    entity = new Qt3DCore::QEntity(root);

    material = new Material();
    transformGlobal = new Transform();
    transformLocal = new Transform();

    entity->addComponent(material);
    entity->addComponent(transformGlobal);

    apply(json);
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

void Object::apply(const QJsonObject json) {
    if(json.contains("transform")) {
        const QJsonObject transform = json["transform"].toObject();

        transformLocal->apply(transform);

        update();
    }

    if(json.contains("material")) {
        const QJsonObject transform = json["material"].toObject();

        material->apply(transform);
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

Qt3DCore::QEntity * Object::getRoot() {
    return Object::root;
}

}
