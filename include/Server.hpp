#ifndef SERVER_HPP
#define SERVER_HPP

#include "BookManager.hpp"
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
#include <string>
#include <sstream>

#define SERVERPORT 8989
#define BUFFSIZE 4096
#define SOCKETERROR (-1)
#define SERVER_BACKLOG 50

typedef struct sockaddr_in SA_IN;
typedef struct sockaddr SA;

class Server {
  private:
    BookManager exchange;
    bool is_running;
    void handle_connection(int client_socket);
  public:
    Server();
    void run();
    void quit();
};

#endif
