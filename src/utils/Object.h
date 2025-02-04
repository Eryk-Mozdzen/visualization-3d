#pragma once

#include <Qt3DExtras>
#include <Qt3DRender>
#include <QJsonObject>

#include "utils/Material.h"
#include "utils/Transform.h"

namespace utils {

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
    Object(const QJsonObject json);
    ~Object();

    void addChild(const QString name, Object *child);
    Object * getChild(const QString name);
    void update();
    void apply(const QJsonObject json);

    Material * getMaterial() const;
    Transform * getTransformGlobal() const;
    Transform * getTransformLocal() const;

    static Qt3DCore::QEntity * getRoot();
};

}
