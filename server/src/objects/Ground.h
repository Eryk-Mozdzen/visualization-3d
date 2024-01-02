#pragma once

#include "Object.h"

namespace gs {

class Ground : public Object {
public:
    Ground(Qt3DCore::QEntity *root, QTextStream &stream);
};

}
