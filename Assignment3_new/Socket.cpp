#include "SocketException.hpp"
#include "Socket.hpp"

#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cerrno>

Socket::Socket() {
    memset(&_sockAddr, 0, sizeof(_sockAddr));

    int sockResult = socket(PF_INET, SOCK_STREAM, 0);
    if (sockResult == -1) {
        throw SocketException(strerror(errno));
    }
    _sockFD = sockResult;

    int optionValue = 1;
    sockResult = setsockopt(_sockFD, SOL_SOCKET, SO_REUSEADDR, &optionValue, sizeof(optionValue));
    if (sockResult == -1) {
        throw SocketException(strerror(errno));
    }
}

Socket::Socket(const int sockFD) : Socket() {
    memset(&_sockAddr, 0, sizeof(_sockAddr));

    this->_sockFD = sockFD;
}

Socket &Socket::bind(const int port) {
    _sockAddr.sin_family = AF_INET;
    _sockAddr.sin_addr.s_addr = INADDR_ANY;
    _sockAddr.sin_port = htons(port);
    if (::bind(this->_sockFD, (struct sockaddr *) &_sockAddr, sizeof(_sockAddr)) == -1) {
        throw SocketException(strerror(errno));
    }
    return (*this);
}

Socket &Socket::close() {
    if (::close(_sockFD) == -1) {
        throw SocketException(strerror(errno));
    }
    return (*this);
}
