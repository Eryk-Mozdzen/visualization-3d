#pragma once

#include <Qt3DCore>

namespace gs {

class Transform : public Qt3DCore::QTransform {
    static constexpr float rad2deg = 180/3.1415;
    static constexpr float deg2rad = 3.1415/180;

public:
    friend QTextStream & operator>>(QTextStream &stream, Transform &transform);
    friend QDebug operator<<(QDebug stream, const Transform &transform);
};

}
