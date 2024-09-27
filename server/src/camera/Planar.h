#pragma once

#include "camera/AbstractCamera.h"

namespace camera {

class Planar : public AbstractCamera {
    float zoom = 0.01;

    void cameraSetup(Qt3DRender::QCamera *camera);
    void moveCamera(const InputState &state, float dt);

public:
    Planar(Qt3DExtras::Qt3DWindow *window);
};

}
