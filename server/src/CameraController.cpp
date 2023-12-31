#include "CameraController.h"
#include <QDebug>

namespace gs {

CameraController::CameraController(Qt3DCore::QNode *parent) : Qt3DExtras::QAbstractCameraController(parent) {

}

void CameraController::moveCamera(const InputState &state, float dt) {
    Qt3DRender::QCamera *camera = this->camera();

    if(camera==nullptr) {
        return;
    }

    if(state.rightMouseButtonActive) {
        const QVector3D up(0, 1, 0);

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
