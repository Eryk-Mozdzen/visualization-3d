#include "Material.h"

namespace gs {

Material::Material() {
    setAmbient(QColor(128, 128, 128));
    setDiffuse(QColor(128, 128, 128));
}

void Material::setColor(int r, int g, int b) {
    setAmbient(QColor(128, 128, 128));
    setDiffuse(QColor(r, g, b));
}

std::istream & operator>>(std::istream &stream, Material &material) {
    int r, g, b;

    stream >> r >> g >> b;

    material.setAmbient(QColor(128, 128, 128));
    material.setDiffuse(QColor(r, g, b));

    return stream;
}

}
