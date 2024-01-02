#pragma once

class Client {
    static constexpr int port = 8080;

    int _socket;

public:
    Client();
    ~Client();

    void write(const std::string &message);
};
