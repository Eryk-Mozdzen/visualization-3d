#pragma once

#include <Qt3DExtras>

#include "Server.h"
#include "CameraController.h"
#include "utils/Object.h"
#include "primitives/Ground.h"

class Window : public Qt3DExtras::Qt3DWindow {
    Q_OBJECT

    Server server;
    CameraController controller;

    primitives::Ground *ground;
    QMap<QString, utils::Object *> objects;

    utils::Object *findLeaf(QList<QString> tree);

public slots:
    void receive(QString line);

public:
    Window();
};
