#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <map>
#include "ServerSocket.hpp"
//#include <Message/HTTPRequest.hpp>
//#include <Message/HTTPResponse.hpp>
//#include <Servlet/TestServlet.hpp>
#include<pthread.h> //for threading , link with lpthread

//the thread function
void *connection_handler(void *);

//std::map<std::string, Servlet&> ServletManager::_servletRegistry = std::map<std::string, Servlet&>();

int main() {
    ServerSocket serverSock = ServerSocket();
    //ServletManager manager;
    try {
        serverSock.bind(5009);
        serverSock.listen();
        while(true) {
            pthread_t thread_id;
            ServerSocket connectionSock = serverSock.accept();
            
            std::string message = connectionSock.receive();
            std::cout << message;
            connectionSock.send("hello");
            if( pthread_create( &thread_id , NULL ,  connection_handler , (void*) &connectionSock) < 0)
            {
                perror("could not create thread");
                return 1;
            }
            
            
//            int processID = fork();
//            if (processID == 0) {
//                // this is the parent process
//                connectionSock.close();
//            } else {
////                connectionSock.send(response.toString());
//                connectionSock.close();
//            }
        }
    } catch (std::exception &e) {
        serverSock.close();
        std::cout << "Caught terminal exception : " << e.what() << std::endl;
        return 1;
    }
}
void *connection_handler(void *socket_desc)
{
    //Get the socket descriptor
    ServerSocket sock = *(ServerSocket*)socket_desc;
    int read_size;
    std::string message , client_message[2000];
    std::cout << "Thread";
    sock.send("Returnnnnnn");
//    //Send some messages to the client
//    message = "Greetings! I am your connection handler\n";
//    write(sock , message , strlen(message));
//    
//    message = "Now type something and i shall repeat what you type \n";
//    write(sock , message , strlen(message));
//    
//    //Receive a message from client
//    while( (read_size = recv(sock , client_message , 2000 , 0)) > 0 )
//    {
//        //end of string marker
//        client_message[read_size] = '\0';
//        
//        //Send the message back to client
//        write(sock , client_message , strlen(client_message));
//        
//        //clear the message buffer
//        memset(client_message, 0, 2000);
//    }
//    
//    if(read_size == 0)
//    {
//        puts("Client disconnected");
//        fflush(stdout);
//    }
//    else if(read_size == -1)
//    {
//        perror("recv failed");
//    }
    
    return 0;
}

