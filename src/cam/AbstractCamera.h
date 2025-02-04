#pragma once

#include <Qt3DExtras>
#include <Qt3DCore>

namespace cam {

class AbstractCamera : public Qt3DExtras::QAbstractCameraController {
    Q_OBJECT

protected:
    Qt3DExtras::Qt3DWindow *window;

    virtual void cameraSetup(Qt3DRender::QCamera *camera) = 0;
    virtual void moveCamera(const InputState &state, float dt) = 0;

public:
    AbstractCamera(Qt3DExtras::Qt3DWindow *window);
    void link();

    void setCenter(const QVector3D center);
};

}
