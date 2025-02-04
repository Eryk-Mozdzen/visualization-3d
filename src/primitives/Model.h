#pragma once

#include "utils/Object.h"

namespace primitives {

class Model : public utils::Object {
public:
    Model(const QJsonObject json);
};

}
