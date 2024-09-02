#include "ArgumentStream.h"

namespace utils {

ArgumentStream::ArgumentStream() {

}

ArgumentStream::ArgumentStream(const QString line) : args{line.split(' ', Qt::SkipEmptyParts)} {

}

bool ArgumentStream::fetch(const QString command) {
    const int index = args.indexOf(command);

    if(index==-1) {
        return false;
    }

    iterator = args.erase(args.begin() + index);

    return true;
}

ArgumentStream & operator>>(ArgumentStream &stream, QString &str) {
    str = *stream.iterator;
    stream.iterator = stream.args.erase(stream.iterator);
    return stream;
}

ArgumentStream & operator>>(ArgumentStream &stream, double &num) {
    num = stream.iterator->toDouble();
    stream.iterator = stream.args.erase(stream.iterator);
    return stream;
}

ArgumentStream & operator>>(ArgumentStream &stream, float &num) {
    num = stream.iterator->toFloat();
    stream.iterator = stream.args.erase(stream.iterator);
    return stream;
}

ArgumentStream & operator>>(ArgumentStream &stream, int &num) {
    num = stream.iterator->toInt();
    stream.iterator = stream.args.erase(stream.iterator);
    return stream;
}

}
