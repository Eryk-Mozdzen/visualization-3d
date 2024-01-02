#pragma once

#include <QTcpServer>
#include <QTcpSocket>

namespace gs {

class Server : public QTcpServer {
    Q_OBJECT

    static constexpr int port = 8080;

protected:
    void incomingConnection(qintptr socketDescriptor) override;

public:
    explicit Server(QObject *parent = nullptr);

signals:
    void receive(QString line);
};

}
