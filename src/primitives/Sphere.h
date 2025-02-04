#pragma once

#include "utils/Object.h"

namespace primitives {

class Sphere : public utils::Object {
public:
    Sphere(const QJsonObject json);
};

}
