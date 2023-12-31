#include "Transform.h"

namespace gs {

std::istream & operator>>(std::istream &stream, Transform &transform) {
    float roll, pitch, yaw;
    float x, y, z;

    stream >> roll >> pitch >> yaw >> x >> y >> z;

    transform.setTranslation(QVector3D(x, y, z));
    transform.setRotationX(roll);
    transform.setRotationY(pitch);
    transform.setRotationZ(yaw);

    return stream;
}

}
