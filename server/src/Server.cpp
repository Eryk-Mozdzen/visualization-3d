#include "Server.h"

namespace gs {

Server::Server(QObject *parent) : QTcpServer(parent) {
    if(!this->listen(QHostAddress::Any, Server::port)) {
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

}
