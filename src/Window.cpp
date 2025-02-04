#include "Window.h"
#include "cam/Orbit.h"
#include "cam/Planar.h"
#include "utils/Object.h"
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

    camera = new cam::Orbit(this);
    camera->link();
}

utils::Object *Window::getObject(QList<QString> tree) {
    if(tree.isEmpty()) {
        return nullptr;
    }

    utils::Object *object = objects.value(tree.front());

    if(object==nullptr) {
        return nullptr;
    }

    tree.pop_front();

    for(const QString &child : tree) {
        object = object->getChild(child);

        if(object==nullptr) {
            return nullptr;
        }
    }

    return object;
}

void Window::receive(const QJsonObject json) {
    if(!json.contains("command")) {
        return;
    }

    if(json["command"]=="clear") {
        QMap<QString, utils::Object *>::iterator it = objects.begin();

        while(it!=objects.end()) {
            delete it.value();
            it = objects.erase(it);
        }
    } else if(json["command"]=="config") {
        if(json.contains("theme")) {
            const QString mode = json["theme"].toString();

            if(mode=="light") {
                defaultFrameGraph()->setClearColor(Qt::white);
                ground.setColors(QColor(220, 220, 220), Qt::red, Qt::green);
            } else if(mode=="dark") {
                defaultFrameGraph()->setClearColor(Qt::black);
                ground.setColors(QColor(128, 128, 128), Qt::darkRed, Qt::darkGreen);
            }
        }

        if(json.contains("camera")) {
            const QString mode = json["camera"].toString();

            cam::AbstractCamera *cam = nullptr;

            if(mode=="orbit") {
                cam = new cam::Orbit(this);
            } else if(mode=="planar") {
                cam = new cam::Planar(this);
            }

            if(cam) {
                delete camera;
                camera = cam;
                camera->link();
            }
        }
    } else if(json["command"]=="create") {
        if(!json.contains("path")) {
            return;
        }

        QList<QString> tree = json["path"].toString().split('/');
        const QString name = tree.back();
        tree.pop_back();

        utils::Object *parent = getObject(tree);
        utils::Object *child = nullptr;

        if(json.contains("geometry")) {
            const QJsonObject geometry = json["geometry"].toObject();

            if(geometry.contains("shape")) {
                const QString shape = geometry["shape"].toString();

                if(shape=="cuboid") {
                    child = new primitives::Cuboid(json);
                } else if(shape=="sphere") {
                    child = new primitives::Sphere(json);
                } else if(shape=="cylinder") {
                    child = new primitives::Cylinder(json);
                } else if(shape=="model") {
                    child = new primitives::Model(json);
                } else if(shape=="empty") {
                    child = new primitives::Empty(json);
                }
            }
        }

        if(child==nullptr) {
            child = new primitives::Empty(json);
        }

        if(parent==nullptr) {
            objects[name] = child;
        } else {
            parent->addChild(name, child);
        }

    } else if(json["command"]=="update") {
        if(!json.contains("path")) {
            return;
        }

        const QList<QString> tree = json["path"].toString().split('/');

        utils::Object *object = getObject(tree);

        if(object) {
            object->apply(json);
        }
    } else if(json["command"]=="camera") {
        if(json.contains("position")) {
            const QJsonArray position = json["position"].toArray();

            if(position.size()==3) {
                const double x = position[0].toDouble();
                const double y = position[1].toDouble();
                const double z = position[2].toDouble();

                camera->setCenter(QVector3D(x, y, z));
            }
        }
    }
}
