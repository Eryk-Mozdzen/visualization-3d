#pragma once

class Client {
    int sock;

public:
    Client();
    ~Client();

    void write(std::string message);
};
