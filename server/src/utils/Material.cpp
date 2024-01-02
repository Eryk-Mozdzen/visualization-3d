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

QTextStream & operator>>(QTextStream &stream, Material &material) {
    QString attribute;
    stream >> attribute;

    int r, g, b;
    stream >> r >> g >> b;

    material.setAmbient(QColor(128, 128, 128));
    material.setDiffuse(QColor(r, g, b));

    return stream;
}

QDebug operator<<(QDebug stream, const Material &material) {

    stream << material.diffuse().red() << material.diffuse().green() << material.diffuse().blue();

    return stream;
}

}
