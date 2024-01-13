#pragma once

#include <Qt3DExtras>

#include "ArgumentStream.h"

namespace gs {

class Material : public Qt3DExtras::QPhongMaterial {
public:
    Material();

    void setColor(int r, int g, int b);

    friend ArgumentStream & operator>>(ArgumentStream &stream, Material &material);
    friend QDebug operator<<(QDebug stream, const Material &material);
};

}
