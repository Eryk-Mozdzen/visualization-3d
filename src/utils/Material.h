#pragma once

#include <Qt3DExtras>
#include <QJsonObject>

namespace utils {

class Material : public Qt3DExtras::QPhongMaterial {
public:
    Material();

    void apply(const QJsonObject material);
    void setColor(int r, int g, int b);

    friend QDebug operator<<(QDebug stream, const Material &material);
};

}
