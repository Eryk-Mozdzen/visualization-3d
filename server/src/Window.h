#pragma once

#include <QVector>
#include <QtWidgets>
#include <Qt3DExtras>
#include <Qt3DRender>

#include "Object.h"
#include "Server.h"

class Window : public Qt3DExtras::Qt3DWindow {
    Q_OBJECT

    QMap<QString, gs::Object *> objects;

    gs::Server server;

    gs::Object * findLeaf(QList<QString> tree);

public slots:
    void receive(QString line);

public:
    Window();
};
