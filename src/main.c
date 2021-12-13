#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv)
{

    printf("Hello World\r\n");

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

    return 0;

}