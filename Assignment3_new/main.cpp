#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <vector>
#include "ServerSocket.hpp"
#include <sstream>
//#include <Message/HTTPRequest.hpp>
//#include <Message/HTTPResponse.hpp>
//#include <Servlet/TestServlet.hpp>
#include<pthread.h> //for threading , link with lpthread
#define MAX_THREADS 6

typedef struct {
    struct sockaddr_in addr;   	/* Client remote address */
    int connfd;					/* Connection file descriptor */
    int uid;			   		/* Client unique identifier */
    char name[32];		 		/* Client name */
} client_t;

#define MAX_CLIENTS		100

client_t *clients[MAX_CLIENTS];

/* Add client to queue */
void queue_add(client_t *cl){
    int i;
    for(i=0;i<MAX_CLIENTS;i++){
        if(!clients[i]){
            clients[i] = cl;
            return;
        }
    }
}

/* Delete client from queue */
void queue_delete(int uid){
    int i;
    for(i=0;i<MAX_CLIENTS;i++){
        if(clients[i]){
            if(clients[i]->uid == uid){
                clients[i] = NULL;
                return;
            }
        }
    }
}

//the thread function
void *connection_handler(void *);
void broadcast();
pthread_t threads[MAX_THREADS];
//std::map<std::string, Servlet&> ServletManager::_servletRegistry = std::map<std::string, Servlet&>();
//std::vector<ServerSocket> clients;
int main() {
    
    ServerSocket serverSock = ServerSocket();
    //ServletManager manager;
    try {
        serverSock.bind(5009);
        serverSock.listen();
        int i = 0;
        int rc;
        
        pthread_t thread_id;
        while(i < MAX_THREADS) {
 
            ServerSocket connectionSock = serverSock.accept();
            
            //clients.push_back(connectionSock);
            //std::cout << clients.size();
            //connectionSock.send("hello");
//            if( pthread_create( &threads[1] , NULL ,  connection_handler , (void*) &connectionSock) < 0)
//            {
//                perror("could not create thread");
//                return 1;
//            }
          //  if (i >= 0 && i < MAX_THREADS) { //Tell that the client cannot connect passed the set amount
                rc = pthread_create(&threads[i], NULL, connection_handler, (void *)&connectionSock);
                //std::cout << "Threads: " << i << "\n";
                //i +=1;
           // }

            
//            int processID = fork();
//            if (processID == 0) {
//                // this is the parent process
//                connectionSock.close();
//            } else {
////                connectionSock.send(response.toString());
//                connectionSock.close();
//            }
            i++;
        }
        
        for(int j = 0; i < MAX_THREADS; j++)
        {
            pthread_join(threads[j], NULL);
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
    //std::cout << "Thread";
    std::stringstream sstm;
    sstm << "Thread No: " << pthread_self() << std::endl;
    message = sock.receive();
    std::cout << message;
    if (message == "ok"){
        broadcast();
    } else
    sock.send(sstm.str());
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

void broadcast(){
    std::stringstream sstm;
    //sstm << clients.size();
//    for (int i = 0; i < MAX_CLIENTS; i++){
//    //    clients[i].send(sstm.str());
//        clients[i]->
//        
//    }
    for (int i = 0; i < MAX_THREADS;i++){
        pthread
    }
}
