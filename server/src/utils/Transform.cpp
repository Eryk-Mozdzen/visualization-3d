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
            transform.setRotationX(Transform::rad2deg*roll);
            transform.setRotationY(Transform::rad2deg*pitch);
            transform.setRotationZ(Transform::rad2deg*yaw);
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

    stream << Transform::deg2rad*transform.rotationX() << Transform::deg2rad*transform.rotationY() << Transform::deg2rad*transform.rotationZ();
    stream << transform.translation().x() << transform.translation().y() << transform.translation().z();
    stream << transform.scale3D().x() << transform.scale3D().y() << transform.scale3D().z();

    return stream;
}

}
