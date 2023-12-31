#pragma once

#include "Object.h"

namespace gs {

class Model : public Object {
public:
    Model(Qt3DCore::QEntity *root, const QString path);
};

}
