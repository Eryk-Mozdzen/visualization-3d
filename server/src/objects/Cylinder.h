#pragma once

#include "Object.h"

namespace gs {

class Cylinder : public Object {
public:
    Cylinder(Qt3DCore::QEntity *root, QTextStream &stream);
};

}
