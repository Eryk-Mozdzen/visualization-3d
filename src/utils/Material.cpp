#include <Qt3DExtras>
#include <QJsonObject>

#include "Material.h"

namespace utils {

Material::Material() {
    setAmbient(QColor(128, 128, 128));
    setDiffuse(QColor(128, 128, 128));
}

void Material::setColor(int r, int g, int b) {
    setAmbient(QColor(128, 128, 128));
    setDiffuse(QColor(r, g, b));
}

void Material::apply(const QJsonObject material) {

    if(material.contains("color")) {
        const QJsonArray color = material["color"].toArray();

        if(color.size()==3) {
            const double r = color[0].toDouble();
            const double g = color[1].toDouble();
            const double b = color[2].toDouble();

            setAmbient(QColor(128, 128, 128));
            setDiffuse(QColor(r, g, b));
        }
    }
}

QDebug operator<<(QDebug stream, const Material &material) {

    stream << material.diffuse().red() << material.diffuse().green() << material.diffuse().blue();

    return stream;
}

}
