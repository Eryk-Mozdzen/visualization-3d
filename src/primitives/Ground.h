#pragma once

#include <Qt3DExtras>

#include "utils/Object.h"

namespace primitives {

class Ground : public utils::Object {
    Qt3DExtras::QPhongMaterial *material_x;
    Qt3DExtras::QPhongMaterial *material_y;

public:
    Ground();

    void setColors(const QColor grid, const QColor x, const QColor y);
};

}
