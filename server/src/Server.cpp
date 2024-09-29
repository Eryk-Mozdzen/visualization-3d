#include <QTcpServer>
#include <QTcpSocket>

#include "Server.h"

Server::Server(QObject *parent) : QTcpServer{parent} {
    this->listen(QHostAddress::LocalHost, 8080);
}

void Server::incomingConnection(qintptr socketDescriptor) {
    QTcpSocket *socket = new QTcpSocket(this);

    if(socket->setSocketDescriptor(socketDescriptor)) {
        connect(socket, &QTcpSocket::readyRead, this, [this, socket]() {
            const QList<QByteArray> lines = socket->readAll().split('\n');

            for(const QByteArray &line : lines) {
                if(line.size()>0) {
                    receive(line);
                }
            }
        });

        connect(socket, &QTcpSocket::disconnected, this, [socket]() {
            socket->deleteLater();
        });
    } else {
        socket->deleteLater();
    }
}
