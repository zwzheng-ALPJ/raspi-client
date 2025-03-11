#ifndef TCP_CILENT_H
#define TCP_CILENT_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#include "logger.h"

class CTcpClient
{
public:
    CTcpClient();
    int Connect(const char* server_addr,int port);
    int Send(const char* message);
    void Receive();
    void Close();

private:
    int sockfd;
    struct sockaddr_in srvaddr;
    char recv_content[128];
};

#endif // TCP_CILENT_H
