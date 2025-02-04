#pragma once

#include "cam/AbstractCamera.h"

namespace cam {

class Orbit : public AbstractCamera {
    InputState last;

    void cameraSetup(Qt3DRender::QCamera *camera);
    void moveCamera(const InputState &state, float dt);

public:
    Orbit(Qt3DExtras::Qt3DWindow *window);
};

}
