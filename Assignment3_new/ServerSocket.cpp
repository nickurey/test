#include "SocketException.hpp"
#include "ServerSocket.hpp"
#include <cstring>
#include <cerrno>

#include <iostream>

ServerSocket& ServerSocket::listen() {
    int listenResult = ::listen(_sockFD, _connectionLimit);
    
    if (listenResult == -1) {
        throw SocketException(strerror(errno));
    }
    
    return (*this);
}

ServerSocket& ServerSocket::accept() {
    socklen_t addressLength = sizeof(this->_sockAddr);
    int acceptResult = ::accept(_sockFD, (sockaddr *) &_sockAddr, &addressLength);
    
    if (acceptResult == -1) {
        throw new SocketException(strerror(errno));
    }
    ServerSocket &connectionSock = (*new ServerSocket(*this));
    connectionSock._sockAddr = this->_sockAddr;
    connectionSock._sockFD = acceptResult;
    return connectionSock;
}

void ServerSocket::send(std::string message) const {
    int sendResult = ::send(_sockFD, message.c_str(), (int) message.size(), 0);
    
    if (sendResult == -1) {
        throw new SocketException(strerror(errno));
    }
}

std::string ServerSocket::receive() const {
    char messageBuffer[MAX_RECIEVE_LENGTH + 1];
    std::string message = "";
    
    int recieveResult = MAX_RECIEVE_LENGTH;
    do {
        memset(messageBuffer, 0, MAX_RECIEVE_LENGTH + 1);
        recieveResult = ::recv(_sockFD, messageBuffer, MAX_RECIEVE_LENGTH, 0);
        message.append(messageBuffer);
    } while (recieveResult == MAX_RECIEVE_LENGTH);
    
    if (recieveResult == -1) {
        throw new SocketException(strerror(errno));
    }
    
    return message;
}