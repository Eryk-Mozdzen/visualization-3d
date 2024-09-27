#pragma once

#include "cam/AbstractCamera.h"

namespace cam {

class Planar : public AbstractCamera {
    float zoom = 0.01;
    InputState last;

    void cameraSetup(Qt3DRender::QCamera *camera);
    void moveCamera(const InputState &state, float dt);

public:
    Planar(Qt3DExtras::Qt3DWindow *window);
};

}
