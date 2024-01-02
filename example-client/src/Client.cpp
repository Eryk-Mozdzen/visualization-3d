#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "Client.h"

Client::Client() {

    _socket = socket(AF_INET, SOCK_STREAM, 0);

    if(_socket==-1) {
        std::cerr << "error creating socket" << std::endl;
        return;
    }

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(Client::port);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(connect(_socket, (struct sockaddr *)&serverAddr, sizeof(serverAddr))==-1) {
        std::cerr << "connection failed" << std::endl;
        return;
    }
}

Client::~Client() {
    close(_socket);
}

void Client::write(const std::string &message) {
    if(send(_socket, message.c_str(), message.size(), 0)==-1) {
        std::cerr << "failed to send message" << std::endl;
    }
}
