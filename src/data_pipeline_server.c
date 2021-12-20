#include "data_pipeline_server.h"

/**
 * TODO:
 * 
 * Essentials:
 * - Complete queue_sockets
 * - Complete (threaded) data source connecting function
 * - Complete dp_api_handler_add()
 * - Complete dp_api_service() for main loop
 * 
 * Priority:
 * - data_pipeline_protocol
 * 
 */

void example_task (void* input_package)
{
    threadPkg *host_input = input_package;

    int tid = pthread_self();

    // connect to socket

    while(host_input->cmd != thread_cmd_quit)
    {

        // wait for messages
        // add SocketObject to queue when a new message is received

    }

    // close connection

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