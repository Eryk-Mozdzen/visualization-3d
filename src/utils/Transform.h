#pragma once

#include <Qt3DCore>
#include <QJsonObject>

namespace utils {

class Transform : public Qt3DCore::QTransform {
public:
    void apply(const QJsonObject transform);
    friend QDebug operator<<(QDebug stream, const Transform &transform);
};

}
