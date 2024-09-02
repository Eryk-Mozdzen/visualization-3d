#include <Qt3DExtras>
#include <Qt3DRender>

#include "Object.h"
#include "utils/Material.h"
#include "utils/Transform.h"
#include "utils/ArgumentStream.h"

namespace utils {

Qt3DCore::QEntity *Object::root = new Qt3DCore::QEntity();

Object::Object(ArgumentStream &stream) : parent{nullptr} {
    entity = new Qt3DCore::QEntity(root);

    material = new Material();
    transformGlobal = new Transform();
    transformLocal = new Transform();

    entity->addComponent(material);
    entity->addComponent(transformGlobal);

    if(stream.fetch("transform")) {
        stream >> *transformLocal;
        update();
    }

    if(stream.fetch("material")) {
        stream >> *material;
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

Qt3DCore::QEntity * Object::getRoot() {
    return Object::root;
}

ArgumentStream & operator>>(ArgumentStream &stream, Object &object) {

    if(stream.fetch("transform")) {
        stream >> *object.transformLocal;
        object.update();
    }

    if(stream.fetch("material")) {
        stream >> *object.material;
    }

    return stream;
}

}
