#include "Object.h"

namespace gs {

Object::Object(Qt3DCore::QEntity *root) : parent{nullptr} {
    entity = new Qt3DCore::QEntity(root);

    material = new Material();
    transformGlobal = new Transform();
    transformLocal = new Transform();

    entity->addComponent(material);
    entity->addComponent(transformGlobal);
}

void Object::addChild(Object *child) {
    child->parent = this;
    childs.push_back(child);
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

}
