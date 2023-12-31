#pragma once

#include <QVector>
#include <QtWidgets>
#include <Qt3DExtras>
#include <Qt3DRender>

#include "Object.h"

class Window : public Qt3DExtras::Qt3DWindow {
    Q_OBJECT

    QVector<gs::Object *> objects;

    Qt3DCore::QEntity *root;

public:
    Window();
};
