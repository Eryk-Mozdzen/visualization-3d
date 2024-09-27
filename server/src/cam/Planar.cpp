#include "cam/Planar.h"

namespace cam {

Planar::Planar(Qt3DExtras::Qt3DWindow *window) : AbstractCamera{window} {

}

void Planar::cameraSetup(Qt3DRender::QCamera *camera) {
    camera->lens()->setOrthographicProjection(
        -zoom*window->width()/2,
        +zoom*window->width()/2,
        -zoom*window->height()/2,
        +zoom*window->height()/2,
        0, 10
    );
    camera->setPosition(QVector3D(0, 0, 1));
    camera->setViewCenter(QVector3D(0, 0, 0));
}

void Planar::moveCamera(const InputState &state, float dt) {
    Qt3DRender::QCamera *camera = this->camera();

    if(camera==nullptr) {
        return;
    }

    camera->setViewCenter(QVector3D(
        camera->viewCenter().x(),
        camera->viewCenter().y(),
        0
    ));

    camera->setPosition(QVector3D(
        camera->viewCenter().x(),
        camera->viewCenter().y(),
        1
    ));

    camera->setUpVector(QVector3D(0, 1, 0));

    camera->lens()->setOrthographicProjection(
        -zoom*window->width()/2,
        +zoom*window->width()/2,
        -zoom*window->height()/2,
        +zoom*window->height()/2,
        0, 10
    );

    if(state.tzAxisValue!=0) {
        zoom +=state.tzAxisValue*dt*zoom*10;
    }

    if(state.rightMouseButtonActive) {
        camera->translateWorld(QVector3D(
            -dt*(state.rxAxisValue + last.rxAxisValue)*0.5*zoom*window->width()/2,
            -dt*(state.ryAxisValue + last.ryAxisValue)*0.5*zoom*window->height()/2,
            0
        ));
    }

    last = state;
}

}
