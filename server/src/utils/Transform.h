#pragma once

#include <Qt3DCore>

namespace gs {

class Transform : public Qt3DCore::QTransform {
public:
    friend QTextStream & operator>>(QTextStream &stream, Transform &transform);
    friend QDebug operator<<(QDebug stream, const Transform &transform);
};

}
