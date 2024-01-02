#include "Server.h"

namespace gs {

Server::Server(QObject *parent) : QTcpServer(parent) {

    if(this->listen(QHostAddress::Any, Server::port)) {
        qDebug() << "listening on port" << Server::port << "...";
    } else {
        qDebug() << "server could not start";
    }
}

void Server::incomingConnection(qintptr socketDescriptor) {
    QTcpSocket *socket = new QTcpSocket(this);

    if(socket->setSocketDescriptor(socketDescriptor)) {
        connect(socket, &QTcpSocket::readyRead, this, [this, socket]() {
            while(socket->bytesAvailable()>0) {
                const QByteArray data = socket->readAll();
                const QList<QByteArray> lines = data.split('\n');

                for(const QByteArray &line : lines) {
                    if(!line.isEmpty()) {
                        receive(line);
                    }
                }
            }
        });

        connect(socket, &QTcpSocket::disconnected, this, [this, socket]() {
            socket->deleteLater();
        });
    } else {
        socket->deleteLater();
    }
}

}
