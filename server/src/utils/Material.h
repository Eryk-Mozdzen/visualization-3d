#pragma once

#include <Qt3DExtras>

namespace gs {

class Material : public Qt3DExtras::QPhongMaterial {
public:
    Material();

    void setColor(int r, int g, int b);

    friend QTextStream & operator>>(QTextStream &stream, Material &material);
    friend QDebug operator<<(QDebug stream, const Material &material);
};

}
