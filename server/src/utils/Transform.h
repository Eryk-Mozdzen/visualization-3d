#pragma once

#include <istream>

#include <Qt3DCore>

namespace gs {

class Transform : public Qt3DCore::QTransform {
public:
    friend std::istream & operator>>(std::istream &stream, Transform &transform);
};

}
