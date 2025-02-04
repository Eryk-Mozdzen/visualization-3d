#pragma once

#include "utils/Object.h"

namespace primitives {

class Cuboid : public utils::Object {
public:
    Cuboid(const QJsonObject json);
};

}
