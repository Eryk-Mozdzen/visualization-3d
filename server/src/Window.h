#pragma once

#include <Qt3DExtras>

#include "cam/AbstractCamera.h"
#include "utils/Object.h"
#include "primitives/Ground.h"

class Window : public Qt3DExtras::Qt3DWindow {
    Q_OBJECT

    cam::AbstractCamera *camera = nullptr;

    primitives::Ground *ground;
    QMap<QString, utils::Object *> objects;

    utils::Object *findLeaf(QList<QString> tree);

public slots:
    void receive(const QString line);

public:
    Window();
};
