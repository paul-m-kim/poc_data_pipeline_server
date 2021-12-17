#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <wordexp.h>
#include <getopt.h>

#include "helper_sockets.h"
#include "data_pipeline_protocol.h"

#define BUFFER_SIZE 4096
#define PORT_NUMBER 8080

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main (int argc, char **argv)
{

    /**
     * server design
     * a. establish a server
     * b. (main thread) client-server protocol
     * c. get data sources
     * d. create threads to access those data sources
     * +  multiple threads for TCP socket (real-time)
     * +  thread pool for REST API (batch)
     * e. queue up threads for reading (perhaps epoll?)
     * f. read information from other threads into a shared memory block
     * g. send data to client
     * h. exit
     * 
     */

    if (argc != 2) error("Incorrect number of arguments");

    int port_number = atoi(*(argv + 1));

    SocketObject server;
    SocketObject accepted_client;

    char buffer_send[BUFFER_SIZE];
    char buffer_recv[BUFFER_SIZE];

    static const char dp_message_welcome[] = "Welcome to Data Pipeline Server\r\n Enter 'help' for list of available commands \r\n Enter a command and '-h' to get more detail on the command";

    uint16_t buffer_recv_len = 0;

    socket_common_init(&server);
    socket_common_init(&accepted_client);

    socket_common_config(&server, socket_type_server, AF_INET, INADDR_ANY, htons(port_number));

    if (socket_common_fd(&server, SOCK_STREAM) < 0) error("failed to get socket fd");

    if (socket_server_bind(&server, 1) < 0) error("failed to bind socket");

    printf("server listening\r\n");

    if (socket_server_accept(&server, &accepted_client) < 0) error("couldn't accept connection");

    printf("client accepted\r\n");

    // send info about server and available protocols
    socket_client_write(&accepted_client, dp_message_welcome, strlen(dp_message_welcome));

    while(1)
    {

        socket_client_read(&accepted_client, buffer_recv, BUFFER_SIZE, &buffer_recv_len);
        if(buffer_recv_len < 0) error("Couldn't receive from accepted client");

        wordexp_t cli_input_string;

        wordexp(buffer_recv, &cli_input_string, 0);

        dp_api_entry(cli_input_string.we_wordc, cli_input_string.we_wordv);        

        wordfree(&cli_input_string);

    }

    

    printf("%s", buffer_recv);



    return 0;

}