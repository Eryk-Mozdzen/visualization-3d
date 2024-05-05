#pragma once

#include <Qt3DExtras>
#include <Qt3DCore>
#include <Qt3DRender>
#include <Qt3DInput>
#include <QMouseEvent>

namespace gs {

class CameraController : public Qt3DExtras::QAbstractCameraController {
    Q_OBJECT

    InputState last;

protected:
    void moveCamera(const InputState &state, float dt);

public:
    explicit CameraController(Qt3DCore::QNode *parent = nullptr);

    void setCenter(const QVector3D center);
};

}
