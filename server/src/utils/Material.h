#pragma once

#include <Qt3DExtras>

#include "utils/ArgumentStream.h"

namespace utils {

class Material : public Qt3DExtras::QPhongMaterial {
public:
    Material();

    void setColor(int r, int g, int b);

    friend ArgumentStream & operator>>(ArgumentStream &stream, Material &material);
    friend QDebug operator<<(QDebug stream, const Material &material);
};

}
