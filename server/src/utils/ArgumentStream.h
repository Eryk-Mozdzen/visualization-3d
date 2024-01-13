#pragma once

#include <QList>

namespace gs {

class ArgumentStream {
    QList<QString> args;
    QList<QString>::iterator iterator;

public:
    ArgumentStream();
    ArgumentStream(const QString line);
    ArgumentStream(ArgumentStream &) = delete;
    ArgumentStream(ArgumentStream &&) = delete;

    bool fetch(const QString command);

    friend ArgumentStream & operator>>(ArgumentStream &stream, QString &str);
    friend ArgumentStream & operator>>(ArgumentStream &stream, double &num);
    friend ArgumentStream & operator>>(ArgumentStream &stream, float &num);
    friend ArgumentStream & operator>>(ArgumentStream &stream, int &num);
};

}
