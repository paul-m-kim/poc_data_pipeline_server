#ifndef DATA_PIPELINE_SERVER_H
#define DATA_PIPELINE_SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <wordexp.h>
#include <getopt.h>

#include <pthread.h>

#include "helper_sockets.h"
#include "data_pipeline_protocol.h"

#define BUFFER_SIZE 4096

SocketObject data_receive_socket_obj_queue[16];
pthread_mutex_t data_receive_socket_obj_queue_mutex;

typedef enum threadCmds
{

    thread_cmd_run = 0,
    thread_cmd_quit

} threadCmds;

typedef struct threadPkg
{

    threadCmds cmd;
    SocketObject source;

} threadPkg;

typedef struct dataSourceConfig
{

    threadPkg *thread_control;
    // source type: real-time | batch
    // min. time interval
    // API to send to data source server


} dataSourceConfig;

void error(const char *msg)
{
    perror(msg);
    exit(1);
}


#endif