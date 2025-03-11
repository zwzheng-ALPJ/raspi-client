#include "tcp_cilent.h"

CTcpClient::CTcpClient()
{
}

int CTcpClient::Connect(const char* server_addr,int port)
{
    //logger()<<"attempting to connect to server"<<server_addr<<"on port"<<port;
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    memset(&srvaddr,0,sizeof(srvaddr));
    srvaddr.sin_family=AF_INET;
    srvaddr.sin_port=htons(port);
    srvaddr.sin_addr.s_addr=inet_addr(server_addr);
    return connect(sockfd,(struct sockaddr*)&srvaddr,sizeof(srvaddr));
}

int CTcpClient::Send(const char *message)
{
    return send(sockfd,message,strlen(message),0);
}

void CTcpClient::Receive()
{
    while(1)
    {
        memset(recv_content,0,sizeof(recv_content));
        int recv_count=recv(sockfd,recv_content,128,0);
        logger()<<"Received: "<<recv_content;
        if(recv_count==0)
            break;
    }
}

void CTcpClient::Close()
{
    close(sockfd);
}
