#include <sstream>

#include <QTimer>

#include "Window.h"
#include "Ground.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Cuboid.h"
#include "Model.h"
#include "CameraController.h"

Window::Window() {

    setTitle("3D Visualization Server");

    root = new Qt3DCore::QEntity;

    QString str;
    QTextStream stream(&str);
    gs::Object *ground = new gs::Ground(root, stream);
    (void)ground;

    Qt3DRender::QCamera *camera = this->camera();
    camera->lens()->setPerspectiveProjection(45, width()/height(), 0.1, 1000);
    camera->setPosition(QVector3D(20, 10, 20));
    camera->setViewCenter(QVector3D(0, 0, 0));

    gs::CameraController *controller = new gs::CameraController(root);
    controller->setCamera(camera);

    defaultFrameGraph()->setClearColor(Qt::black);
    setRootEntity(root);

    connect(&server, &gs::Server::receive, this, &Window::receive);
}

gs::Object * Window::findLeaf(QList<QString> tree) {
    if(tree.isEmpty()) {
        return nullptr;
    }

    gs::Object *leaf = objects.value(tree.front());

    if(leaf==nullptr) {
        return nullptr;
    }

    tree.pop_front();

    for(const QString &child : tree) {
        leaf = leaf->getChild(child);

        if(leaf==nullptr) {
            return nullptr;
        }
    }

    return leaf;
}

void Window::receive(QString line) {
    //qDebug() << line;

    QTextStream stream(&line);

    QString command;
    stream >> command;

    if(command=="clear") {
        QMap<QString, gs::Object *>::iterator it = objects.begin();
        while(it!=objects.end()) {
            delete it.value();
            it = objects.erase(it);
        }
    } else if(command=="create") {
        QString name;
        QString type;
        stream >> name >> type;

        QList<QString> tree = name.split('.');
        tree.pop_back();

        gs::Object *parent = findLeaf(tree);
        gs::Object *child = nullptr;

        if(type=="cuboid") {
            child = new gs::Cuboid(root, stream);
        } else if(type=="sphere") {
            child = new gs::Sphere(root, stream);
        } else if(type=="cylinder") {
            child = new gs::Cylinder(root, stream);
        } else if(type=="model") {
            child = new gs::Model(root, stream);
        } else {
            qDebug() << "unknown object type";
            return;
        }

        if(parent==nullptr) {
            objects[name] = child;
        } else {
            parent->addChild(name, child);
        }

    } else if(command=="update") {
        QString name;
        stream >> name;

        const QList<QString> tree = name.split('.');

    }
}
