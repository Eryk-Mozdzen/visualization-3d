#pragma once

#include <QVector>
#include <QtWidgets>
#include <Qt3DExtras>
#include <Qt3DRender>

#include "Object.h"
#include "Server.h"

class Window : public Qt3DExtras::Qt3DWindow {
    Q_OBJECT

    QVector<gs::Object *> objects;

    Qt3DCore::QEntity *root;

    gs::Server server;

    void receive(QString line);

public:
    Window();
};
