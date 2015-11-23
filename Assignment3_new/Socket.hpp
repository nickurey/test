#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

class Socket {
  public:
    Socket();
    Socket(int socketFD);

    Socket& bind(const int port);

    Socket& close();

  protected:

    int _sockFD;
    sockaddr_in _sockAddr;
};
