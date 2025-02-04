#pragma once

#include "utils/Object.h"

namespace primitives {

class Empty : public utils::Object {
public:
    Empty(const QJsonObject json);
};

}
