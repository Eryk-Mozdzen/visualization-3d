#pragma once

#include <Qt3DExtras>

#include "Object.h"

namespace gs {

class Ground : public Object {
    Qt3DExtras::QPhongMaterial *material_x;
    Qt3DExtras::QPhongMaterial *material_y;

public:
    Ground(ArgumentStream &stream);

    void setColors(const QColor grid, const QColor x, const QColor y);
};

}
