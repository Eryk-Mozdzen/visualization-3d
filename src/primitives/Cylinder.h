#pragma once

#include "utils/Object.h"

namespace primitives {

class Cylinder : public utils::Object {
public:
    Cylinder(const QJsonObject json);
};

}
