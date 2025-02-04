#include <Qt3DCore>
#include <QJsonObject>

#include "Transform.h"

namespace utils {

void Transform::apply(const QJsonObject transform) {

    if(transform.contains("rpy")) {
        const QJsonArray rpy = transform["rpy"].toArray();

        if(rpy.size()==3) {
            const double roll = rpy[0].toDouble();
            const double pitch = rpy[1].toDouble();
            const double yaw = rpy[2].toDouble();

            const float rollHalf = Transform::deg2rad*roll/2;
            const float pitchHalf = Transform::deg2rad*pitch/2;
            const float yawHalf = Transform::deg2rad*yaw/2;

            const float cosRollHalf = std::cos(rollHalf);
            const float sinRollHalf = std::sin(rollHalf);
            const float cosPitchHalf = std::cos(pitchHalf);
            const float sinPitchHalf = std::sin(pitchHalf);
            const float cosYawHalf = std::cos(yawHalf);
            const float sinYawHalf = std::sin(yawHalf);

            const float w = cosRollHalf * cosPitchHalf * cosYawHalf + sinRollHalf * sinPitchHalf * sinYawHalf;
            const float x = sinRollHalf * cosPitchHalf * cosYawHalf - cosRollHalf * sinPitchHalf * sinYawHalf;
            const float y = cosRollHalf * sinPitchHalf * cosYawHalf + sinRollHalf * cosPitchHalf * sinYawHalf;
            const float z = cosRollHalf * cosPitchHalf * sinYawHalf - sinRollHalf * sinPitchHalf * cosYawHalf;

            setRotation(QQuaternion(w, x, y, z));
        }
    }

    if(transform.contains("quaternion")) {
        const QJsonArray quaternion = transform["rpy"].toArray();

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
