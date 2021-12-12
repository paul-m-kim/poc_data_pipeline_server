/**
 * General:
 * Testing
 * Debug mode
 * logs?
 * Code guidelines
 *   variable format - my_variable
 *   function format - my_function() - module_object_create() / module_object_destroy() / module_object_move()
 *   define format - MY_DEFINE
 *   type format - MyType
 * 
 */

/**
 * Data Pipeline Server Components:
 * n x Data Connector
 * Data Writer (manages data connectors)
 *   Extraction Transformation? and Loading (ETL)
 *   Transformation Examples: parser, joiner, convert (csv, json)
 * Message Queue
 * 
 * Thread:
 * Data Producer (produces data to client)
 * Request Processor (processes requests from client)
 * 
 */

/**
 * External Data Source Server Components
 * 
 */

/**
 * Client Components
 * 
 */

/**
 * API for Client
 * - add data sources (REST/TCP Socket/WebSocket[hard? realtime])
 *   + batch data (duration?)
 *   + real-time data
 * - query data (Data Lake / Data Warehouse)
 *   + text (csv?, json?)
 *   + images
 *   + videos
 * 
 */

/**
 * Server TCP socket
 * socket()
 * bind()
 * listen() - limit number of clients
 * accept()
 * read() (send and receive are different?)
 * write()
 * close()
 * 
 */

/**
 * processes:
 * fork() - child process
 * wait() - reaping child processes (set in GDB)
 * exec() - replaces calling process (set in GDB)
 * sbrk() - program break
 * nmap() - request memory from kernel
 * sigaction() - check for async compatibility
 * 
 * 
 * 
 */

/**
 * threading
 * pthread_mutex_t
 * pthread_mutex_init
 * pthread_mutex_lock
 * pthread_mutex_unlock
 * pthread_t
 * pthread_create()
 * pthread_join()
 * 
 */

/**
 * piping
 * pipe()
 * close()
 * mkfifo() - hangs until another process opens the fifo
 * open() - fcntl.h
 * 
 */

// fprintf
// signal

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define SOCKET_BUFFER_SIZE 256
#define SOCKET_SERVER_PORT_NUMBER 8080

char socket_buffer[SOCKET_BUFFER_SIZE];

void* socket_server_listen(void* port)
{

    // check number of arguments

    int sockfd, newsockfd, portno, n; // port number > 1024
    char buffer[256];

    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen;

    sockfd = scoket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
    {
        // error
    }
 
    //bzero()
    portno = atoi(argv[1]);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if(bing(sockfd, (struct sockaddr *) &serv_addr , sizeor(serv_addr)) < 0)
    {
        // error
    }

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if(newsockfd < 0)
    {
        // error
    }

    while(1)
    {

        // bzero(buffer, 256);
        n = read(newsockfd, buffer, 256);
        if(n < 0)
        {
            // error
        }
        printf("Client : %s\n", buffer);

        // clear buffer?
        fgets(buffer, 256, stdin);

        n = write(newsockfd, buffer, strlen(buffer));
        if(n < 0)
        {
            // error
        }

        int i = strncmp("Bye", buffer, 3);
        if(i == 0)
        {
            break;
        }

    }

    close(newsockfd);
    close(sockfd);

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