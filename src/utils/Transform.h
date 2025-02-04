#pragma once

#include <Qt3DCore>
#include <QJsonObject>

namespace utils {

class Transform : public Qt3DCore::QTransform {
    static constexpr float deg2rad = 3.1415/180;

public:
    void apply(const QJsonObject transform);
    friend QDebug operator<<(QDebug stream, const Transform &transform);
};

}
