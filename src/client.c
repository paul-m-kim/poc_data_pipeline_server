/**
 * client TCP socket
 * socket()
 * conenction()
 * write()
 * read()
 * close()
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <netdb.h> // hostnames, ipv4 addresses

void* socket_server_listen()
{

    

}

void* socket_client_connect()
{

    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    if (argc < 3)
    {
        // error
    }

    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        // error
    }

    server = gethostbyname(argv[1]);
    if (server == NULL)
    {
        // error
    }

    // bzero()

    serv_addr.sin_family = AF_INET;
    bcopy((char*) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);
    
    if(connect(sockfd, (struct scokaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    {
        // error
    }

    while(1)
    {
        // bzero() buffer
        fgets(buffer, 256, stdin);
        n = write(sockfd, buffer, strlen(buffer));
        if (n < 0)
        {
            // error
        }

        // bzero() buffer
        n = read(sockfd, buffer, 256);
        if (n < 0)
        {
            // error
        }

        printf("Server : %s\r\n", buffer);

        int i = strncmp("Bye", buffer, 3);
        if(i == 0)
        {
            break;
        }

    }

    close(sockfd);

}

int main(int argc, char **argv)
{

    
    return 0;

}