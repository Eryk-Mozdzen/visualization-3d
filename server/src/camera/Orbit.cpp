#include "camera/Orbit.h"

namespace camera {

Orbit::Orbit(Qt3DExtras::Qt3DWindow *window) : AbstractCamera{window} {

}

void Orbit::cameraSetup(Qt3DRender::QCamera *camera) {
    camera->lens()->setPerspectiveProjection(45, 16./9., 0.1, 1000);
    camera->setPosition(QVector3D(0, -4, 2));
    camera->setViewCenter(QVector3D(0, 0, 0));
}

void Orbit::moveCamera(const InputState &state, float dt) {
    Qt3DRender::QCamera *camera = this->camera();

    if(camera==nullptr) {
        return;
    }

    if(state.rightMouseButtonActive) {
        const QVector3D up(0, 0, 1);

        camera->panAboutViewCenter(-(state.rxAxisValue + last.rxAxisValue)*0.5*dt*300, up);
        camera->tiltAboutViewCenter(-(state.ryAxisValue + last.ryAxisValue)*0.5*dt*300);
    }

    const float dist = (camera->viewCenter() - camera->position()).length();

    if(state.tzAxisValue!=0) {
        const QVector3D forward(0, 0, 1);

        camera->translate(forward*state.tzAxisValue*dt*dist*10, Qt3DRender::QCamera::DontTranslateViewCenter);
    }

    if(state.middleMouseButtonActive) {
        const QVector3D direction(-(state.rxAxisValue + last.rxAxisValue)*0.5, -(state.ryAxisValue + last.ryAxisValue)*0.5, 0);

        camera->translate(direction*dt*dist);
    }

    last = state;
}

}
