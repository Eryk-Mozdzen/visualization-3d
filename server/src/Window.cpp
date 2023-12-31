#include <QTimer>

#include "Window.h"
#include "Ground.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Cuboid.h"
#include "Model.h"
#include "CameraController.h"

Window::Window() {

    root = new Qt3DCore::QEntity;

    objects.push_back(new gs::Ground(root));
    objects.push_back(new gs::Sphere(root));
    objects.push_back(new gs::Cylinder(root));
    objects.push_back(new gs::Cuboid(root));
    objects.push_back(new gs::Model(root, "/home/emozdzen/Downloads/3DBenchy.stl"));

    objects[1]->getMaterial()->setColor(255, 0, 0);
    objects[1]->getTransformGlobal()->setTranslation(QVector3D(0, 0, 0));

    objects[2]->getMaterial()->setColor(0, 255, 0);
    objects[2]->getTransformGlobal()->setTranslation(QVector3D(0, 3, 0));

    objects[3]->getMaterial()->setColor(0, 0, 255);
    objects[3]->getTransformGlobal()->setTranslation(QVector3D(0, 0, 100));
    objects[3]->addChild(objects[4]);

    objects[4]->getMaterial()->setColor(255, 0, 255);
    objects[4]->getTransformLocal()->setTranslation(QVector3D(0, 0, -3));
    objects[4]->getTransformLocal()->setScale(0.1);
    objects[4]->getTransformLocal()->setRotationX(-90);
    objects[4]->update();

    Qt3DRender::QCamera *camera = this->camera();
    camera->lens()->setPerspectiveProjection(45, width()/height(), 0.1, 1000);
    camera->setPosition(QVector3D(20, 10, 20));
    camera->setViewCenter(QVector3D(0, 0, 0));

    gs::CameraController *controller = new gs::CameraController(root);
    controller->setCamera(camera);

    defaultFrameGraph()->setClearColor(Qt::black);
    setRootEntity(root);

    float *t = new float;
    *t = 0;
    QTimer *timer = new QTimer();
    connect(timer, &QTimer::timeout, [this, t]() {
        this->objects[3]->getTransformGlobal()->setTranslation(10*QVector3D(std::sin(*t), 0, std::cos(*t)));
        this->objects[4]->getTransformLocal()->setRotationY(*t*180/3.1415);
        this->objects[4]->update();

        *t +=0.01;
    });
    timer->start(20);
}
