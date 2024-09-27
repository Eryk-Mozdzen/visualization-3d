#include "Window.h"
#include "camera/Orbit.h"
#include "camera/Planar.h"
#include "utils/Object.h"
#include "utils/ArgumentStream.h"
#include "primitives/Ground.h"
#include "primitives/Sphere.h"
#include "primitives/Cylinder.h"
#include "primitives/Cuboid.h"
#include "primitives/Model.h"
#include "primitives/Empty.h"

Window::Window() {
    setTitle("3D Visualization Server");
    defaultFrameGraph()->setClearColor(Qt::black);
    setRootEntity(utils::Object::getRoot());

    camera = new camera::Orbit(this);
    camera->link();

    utils::ArgumentStream stream;
    ground = new primitives::Ground(stream);
}

utils::Object *Window::findLeaf(QList<QString> tree) {
    if(tree.isEmpty()) {
        return nullptr;
    }

    utils::Object *leaf = objects.value(tree.front());

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
    utils::ArgumentStream stream(line);

    if(stream.fetch("color-mode")) {
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
        QMap<QString, utils::Object *>::iterator it = objects.begin();
        while(it!=objects.end()) {
            delete it.value();
            it = objects.erase(it);
        }
    }

    if(stream.fetch("create")) {
        QString name;
        QString type;
        stream >> name >> type;

        QList<QString> tree = name.split('/');
        name = tree.back();
        tree.pop_back();

        utils::Object *parent = findLeaf(tree);
        utils::Object *child = nullptr;

        if(type=="cuboid") {
            child = new primitives::Cuboid(stream);
        } else if(type=="sphere") {
            child = new primitives::Sphere(stream);
        } else if(type=="cylinder") {
            child = new primitives::Cylinder(stream);
        } else if(type=="model") {
            child = new primitives::Model(stream);
        } else if(type=="empty") {
            child = new primitives::Empty(stream);
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

        const QList<QString> tree = name.split('/');

        utils::Object *object = findLeaf(tree);

        if(object==nullptr) {
            qDebug() << "object does not exist";
            return;
        }

        stream >> *object;
    }

    if(stream.fetch("camera")) {
        float x, y, z;
        stream >> x >> y >> z;

        camera->setCenter(QVector3D(x, y, z));
    }

    if(stream.fetch("camera-mode")) {
        QString mode;
        stream >> mode;

        if(mode=="orbit") {
            if(camera) {
                delete camera;
                camera = nullptr;
            }
            camera = new camera::Orbit(this);
            camera->link();
        } else if(mode=="planar") {
            if(camera) {
                delete camera;
                camera = nullptr;
            }
            camera = new camera::Planar(this);
            camera->link();
        }
    }
}
