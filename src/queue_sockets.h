#ifndef QUEUE_PTHREAD_H
#define QUEUE_PTHREAD_H

#include "helper_sockets.h"

typedef struct SocketObjectQueue
{
    SocketObject *queue;
    int queue_size_max;
    int queue_head;
    int queue_tail;
} SocketObjectQueue;

int thread_queue_create (SocketObjectQueue *queue_obj);
int thread_queue_init (SocketObjectQueue *queue_obj);
int thread_queue_is_empty (SocketObjectQueue *queue_obj);
int thread_queue_destroy (SocketObjectQueue *queue_obj);
int thread_enqueue (SocketObjectQueue *queue_obj, SocketObject socket_obj);
int thread_dequeue (SocketObjectQueue *queue_obj);

#endif