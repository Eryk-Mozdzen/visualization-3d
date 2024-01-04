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
    QMap<QString, Object *> childs;

public:
    Object(Qt3DCore::QEntity *root, QTextStream &stream);
    ~Object();

    void addChild(const QString name, Object *child);
    Object * getChild(const QString name);
    void update();

    Material * getMaterial() const;
    Transform * getTransformGlobal() const;
    Transform * getTransformLocal() const;

    friend QTextStream & operator>>(QTextStream &stream, Object &object);
};

}
