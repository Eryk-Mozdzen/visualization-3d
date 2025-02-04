#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonDocument>

#include "Server.h"

Server::Server(QObject *parent) : QTcpServer{parent} {
    this->listen(QHostAddress::LocalHost, 8080);
}

void Server::incomingConnection(qintptr socketDescriptor) {
    QTcpSocket *socket = new QTcpSocket(this);

    if(socket->setSocketDescriptor(socketDescriptor)) {
        connect(socket, &QTcpSocket::readyRead, this, [this, socket]() {
            QByteArray bytes = socket->readAll();
            QByteArray buffer;

            while(bytes.size()>0) {
                buffer.append(bytes.front());
                bytes.remove(0, 1);

                const QJsonDocument json = QJsonDocument::fromJson(buffer);

                if(!json.isNull()) {
                    receive(json.object());
                    buffer.clear();
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
