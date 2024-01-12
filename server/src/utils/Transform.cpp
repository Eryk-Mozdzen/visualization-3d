#include "Transform.h"

namespace gs {

QTextStream & operator>>(QTextStream &stream, Transform &transform) {
    while(!stream.atEnd()) {
        const QString line = stream.readAll();
        QList<QString> words = line.split(' ');
        words.removeAll(QString());
        const QString first = words.first();

        stream << line;

        if(first!="rotation" && first!="translation" && first!="scale") {
            break;
        }

        QString attribute;
        stream >> attribute;

        if(attribute=="rotation") {
            float roll, pitch, yaw;
            stream >> roll >> pitch >> yaw;

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

            transform.setRotation(QQuaternion(w, x, y, z));

        } else if(attribute=="translation") {
            float x, y, z;
            stream >> x >> y >> z;
            transform.setTranslation(QVector3D(x, y, z));
        } else if(attribute=="scale") {
            float x, y, z;
            stream >> x >> y >> z;
            transform.setScale3D(QVector3D(x, y, z));
        }
    }

    return stream;
}

QDebug operator<<(QDebug stream, const Transform &transform) {

    stream << transform.rotationX() << transform.rotationY() << transform.rotationZ();
    stream << transform.translation().x() << transform.translation().y() << transform.translation().z();
    stream << transform.scale3D().x() << transform.scale3D().y() << transform.scale3D().z();

    return stream;
}

}
