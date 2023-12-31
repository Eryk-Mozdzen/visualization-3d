#pragma once

#include <QtWidgets>
#include <Qt3DExtras>
#include <Qt3DRender>

#include "Material.h"
#include "Transform.h"

namespace gs {

class Object {
protected:
    Qt3DCore::QEntity *entity;
    Material *material;
    Transform *transformGlobal;
    Transform *transformLocal;

    Object *parent;
    QVector<Object *> childs;

    Object(Qt3DCore::QEntity *root);

public:
    void addChild(Object *child);
    void update();

    Material * getMaterial() const;
    Transform * getTransformGlobal() const;
    Transform * getTransformLocal() const;
};

}
