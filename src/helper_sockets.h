/**
 * Socket:
 * 
 * Client:
 * socket() -> connection() -> write() -> read() -> close()
 * 
 * Server:
 * socket() -> bind() -< listen() -> accept() -> read() -> write() -> close()
 * 
 */

#ifndef HELPER_SOCKET_H
#define HELPER_SOCKET_H

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

typedef enum SocketType {
    socket_type_not_set = 0,
    socket_type_server,
    socket_type_client
} SocketType;

typedef enum SocketStatus {
    socket_status_init = 0,
    socket_status_fd,
    socket_status_bind,
    socket_status_listen,
    socket_status_accept,
    socket_status_connected,
    socket_status_closed
} SocketStatus;

typedef struct SocketObject {

    SocketType type;
    SocketStatus status;

    int socket_fd;
    int socket_client_fd;
    int socket_port_no;

    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    
    socklen_t client_length;

} SocketObject;

int socket_object_init(SocketObject *socket_obj);
int socket_object_config(SocketObject *socket_obj, SocketType type, uint16_t sin_family, uint16_t sin_addr, uint16_t sin_port);
int socket_fd(SocketObject *socket_obj, uint16_t socket_type);
int socket_server_init(SocketObject *socket_obj, uint16_t num_connection_request);
int socket_server_accept(SocketObject *socket_obj);
int socket_connect(SocketObject *socket_obj);
int socket_close(SocketObject *socket_obj);
int socket_write(SocketObject *socket_obj, char *string, uint16_t str_len);
int socket_read(SocketObject *socket_obj, char *buffer, uint16_t buffer_size, uint16_t *str_len);

#endif