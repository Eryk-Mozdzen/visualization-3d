#include <cmath>
#include <Qt3DCore>
#include <QJsonObject>

#include "Transform.h"

namespace utils {

void Transform::apply(const QJsonObject transform) {

    if(transform.contains("rpy")) {
        const QJsonArray rpy = transform["rpy"].toArray();

        if(rpy.size()==3) {
            constexpr double deg2rad = M_PI/180;

            const double roll  = deg2rad*rpy[0].toDouble();
            const double pitch = deg2rad*rpy[1].toDouble();
            const double yaw   = deg2rad*rpy[2].toDouble();

            const double cosRollHalf = std::cos(roll/2);
            const double sinRollHalf = std::sin(roll/2);
            const double cosPitchHalf = std::cos(pitch/2);
            const double sinPitchHalf = std::sin(pitch/2);
            const double cosYawHalf = std::cos(yaw/2);
            const double sinYawHalf = std::sin(yaw/2);

            const double w = cosRollHalf * cosPitchHalf * cosYawHalf + sinRollHalf * sinPitchHalf * sinYawHalf;
            const double x = sinRollHalf * cosPitchHalf * cosYawHalf - cosRollHalf * sinPitchHalf * sinYawHalf;
            const double y = cosRollHalf * sinPitchHalf * cosYawHalf + sinRollHalf * cosPitchHalf * sinYawHalf;
            const double z = cosRollHalf * cosPitchHalf * sinYawHalf - sinRollHalf * sinPitchHalf * cosYawHalf;

            setRotation(QQuaternion(w, x, y, z));
        }
    }

    if(transform.contains("quaternion")) {
        const QJsonArray quaternion = transform["quaternion"].toArray();

        if(quaternion.size()==4) {
            const double w = quaternion[0].toDouble();
            const double x = quaternion[1].toDouble();
            const double y = quaternion[2].toDouble();
            const double z = quaternion[3].toDouble();

            setRotation(QQuaternion(w, x, y, z));
        }
    }

    if(transform.contains("translation")) {
        const QJsonArray translation = transform["translation"].toArray();

        if(translation.size()==3) {
            const double x = translation[0].toDouble();
            const double y = translation[1].toDouble();
            const double z = translation[2].toDouble();

            setTranslation(QVector3D(x, y, z));
        }
    }
}

QDebug operator<<(QDebug stream, const Transform &transform) {

    stream << transform.rotationX() << transform.rotationY() << transform.rotationZ();
    stream << transform.translation().x() << transform.translation().y() << transform.translation().z();

    return stream;
}

}
