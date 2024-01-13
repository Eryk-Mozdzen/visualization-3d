#pragma once

#include <QtWidgets>
#include <Qt3DExtras>
#include <Qt3DRender>

#include "Material.h"
#include "Transform.h"
#include "ArgumentStream.h"

namespace gs {

class Object {
    static Qt3DCore::QEntity *root;

protected:
    Qt3DCore::QEntity *entity;
    Material *material;
    Transform *transformGlobal;
    Transform *transformLocal;

    Object *parent;
    QMap<QString, Object *> childs;

public:
    Object(ArgumentStream &stream);
    ~Object();

    void addChild(const QString name, Object *child);
    Object * getChild(const QString name);
    void update();

    Material * getMaterial() const;
    Transform * getTransformGlobal() const;
    Transform * getTransformLocal() const;

    static Qt3DCore::QEntity * getRoot();

    friend ArgumentStream & operator>>(ArgumentStream &stream, Object &object);
};

}
