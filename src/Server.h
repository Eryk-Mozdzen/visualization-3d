#pragma once

#include <QTcpServer>
#include <QJsonObject>

class Server : public QTcpServer {
    Q_OBJECT

protected:
    void incomingConnection(qintptr socketDescriptor) override;

signals:
    void receive(const QJsonObject json);

public:
    Server(QObject *parent=nullptr);
};
