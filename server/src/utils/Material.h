#pragma once

#include <istream>

#include <Qt3DExtras>

namespace gs {

class Material : public Qt3DExtras::QPhongMaterial {
public:
    Material();

    void setColor(int r, int g, int b);

    friend std::istream & operator>>(std::istream &stream, Material &material);
};

}
