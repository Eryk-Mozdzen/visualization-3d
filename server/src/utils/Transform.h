#pragma once

#include <Qt3DCore>

#include "ArgumentStream.h"

namespace gs {

class Transform : public Qt3DCore::QTransform {
    static constexpr float deg2rad = 3.1415/180;

public:
    friend ArgumentStream & operator>>(ArgumentStream &stream, Transform &transform);
    friend QDebug operator<<(QDebug stream, const Transform &transform);
};

}
