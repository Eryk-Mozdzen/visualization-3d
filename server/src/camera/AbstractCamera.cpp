#include "camera/AbstractCamera.h"
#include "utils/Object.h"

namespace camera {

AbstractCamera::AbstractCamera(Qt3DExtras::Qt3DWindow *window) : Qt3DExtras::QAbstractCameraController{utils::Object::getRoot()}, window{window} {

}

void AbstractCamera::link() {
    Qt3DRender::QCamera *camera = window->camera();

    cameraSetup(camera);

    this->setCamera(camera);
}

void AbstractCamera::setCenter(const QVector3D center) {
    Qt3DRender::QCamera *camera = this->camera();

    if(camera==nullptr) {
        return;
    }

    const QVector3D delta = center - camera->viewCenter();

    camera->translateWorld(delta);
}

}
