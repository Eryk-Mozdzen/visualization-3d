#include "Window.h"
#include "Ground.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Cuboid.h"
#include "Model.h"
#include "CameraController.h"
#include "ArgumentStream.h"

Window::Window() {
    setTitle("3D Visualization Server");

    gs::ArgumentStream stream;
    ground = new gs::Ground(stream);

    Qt3DRender::QCamera *camera = this->camera();
    camera->rotate(QQuaternion::fromAxisAndAngle(QVector3D(1, 0, 0), 90));
    camera->lens()->setPerspectiveProjection(45, width()/height(), 0.1, 1000);
    camera->setPosition(QVector3D(0, -4, 2));
    camera->setViewCenter(QVector3D(0, 0, 0));

    controller = new gs::CameraController(gs::Object::getRoot());
    controller->setCamera(camera);

    defaultFrameGraph()->setClearColor(Qt::black);
    setRootEntity(gs::Object::getRoot());

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
    gs::ArgumentStream stream(line);

    if(stream.fetch("mode")) {
        QString mode;
        stream >> mode;

        if(mode=="light") {
            defaultFrameGraph()->setClearColor(Qt::white);
            ground->setColors(QColor(220, 220, 220), Qt::red, Qt::green);
        } else if(mode=="dark") {
            defaultFrameGraph()->setClearColor(Qt::black);
            ground->setColors(QColor(128, 128, 128), Qt::darkRed, Qt::darkGreen);
        }
    }

    if(stream.fetch("clear")) {
        QMap<QString, gs::Object *>::iterator it = objects.begin();
        while(it!=objects.end()) {
            delete it.value();
            it = objects.erase(it);
        }
    }

    if(stream.fetch("create")) {
        QString name;
        QString type;
        stream >> name >> type;

        QList<QString> tree = name.split('.');
        name = tree.back();
        tree.pop_back();

        gs::Object *parent = findLeaf(tree);
        gs::Object *child = nullptr;

        if(type=="cuboid") {
            child = new gs::Cuboid(stream);
        } else if(type=="sphere") {
            child = new gs::Sphere(stream);
        } else if(type=="cylinder") {
            child = new gs::Cylinder(stream);
        } else if(type=="model") {
            child = new gs::Model(stream);
        } else if(type=="empty") {
            child = new gs::Object(stream);
        } else {
            qDebug() << "unknown object type:" << type;
            return;
        }

        if(parent==nullptr) {
            objects[name] = child;
        } else {
            parent->addChild(name, child);
        }
    }

    if(stream.fetch("update")) {
        QString name;
        stream >> name;

        const QList<QString> tree = name.split('.');

        gs::Object *object = findLeaf(tree);

        if(object==nullptr) {
            qDebug() << "object does not exist";
            return;
        }

        stream >> *object;
    }

    if(stream.fetch("camera")) {
        float x, y, z;
        stream >> x >> y >> z;

        controller->setCenter(QVector3D(x, y, z));
    }
}
