#include <QTcpServer>
#include <QTcpSocket>

#include "Server.h"

Server::Server(QObject *parent) : QTcpServer{parent} {
    if(!this->listen(QHostAddress::LocalHost, 8080)) {
        qDebug() << "server could not start";
    }
}

void Server::incomingConnection(qintptr socketDescriptor) {
    QTcpSocket *socket = new QTcpSocket(this);

    if(socket->setSocketDescriptor(socketDescriptor)) {
        connect(socket, &QTcpSocket::readyRead, this, [this, socket]() {
            QList<QByteArray> lines = socket->readAll().split('\n');

            lines.removeAll(QByteArray());

            for(const QByteArray &line : lines) {
                receive(line);
            }
        });

        connect(socket, &QTcpSocket::disconnected, this, [socket]() {
            socket->deleteLater();
        });
    } else {
        socket->deleteLater();
    }
}
