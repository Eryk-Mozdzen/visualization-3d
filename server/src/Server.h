#pragma once

#include <QTcpServer>

class Server : public QTcpServer {
    Q_OBJECT

protected:
    void incomingConnection(qintptr socketDescriptor) override;

signals:
    void receive(const QString line);

public:
    Server(QObject *parent=nullptr);
};
