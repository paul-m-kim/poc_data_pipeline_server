#ifndef DATA_PIPELINE_PROTOCOL_H
#define DATA_PIPELINE_PROTOCOL_H

// Macros
#define xstr(s) str(s)
#define str(s) #s

#define DP_PROTOCOL_VERSION_MAJOR 0
#define DP_PROTOCOL_VERSION_MINOR 1
#define DP_PROTOCOL_VERSION_PATCH 0

/**
 * API To Do:
 * remove tasks
 * add tasks
 * + api call
 * + ip
 * + port
 * + interval
 * pause
 * start
 * status
 * quit
 * 
 */

#include <stdio.h>
#include <unistd.h> // getopt()
#include <string.h>

#define DP_API_DECLARATION(CALL) int dp_api_handler_ ## CALL(int argc, char **argv);
#define DP_API_ADD(CALL) {.call = #CALL, .func = &dp_api_handler_ ## CALL}

typedef int (*dp_api_handler)(int argc, char **argv);



// Not Implemented
enum DPAPIErrors{

    API_FOUND = 0,
    API_NOT_FOUND

};

struct DPAPI{

    char* call;
    dp_api_handler func;

} DPAPI;

int dp_api_entry(int argc, char **argv);

DP_API_DECLARATION(status)
DP_API_DECLARATION(start)
DP_API_DECLARATION(pause)
DP_API_DECLARATION(quit)
DP_API_DECLARATION(list)
DP_API_DECLARATION(add)
DP_API_DECLARATION(remove)

struct DPAPI DPAPIs[] = {

    DP_API_ADD(status),
    DP_API_ADD(start),
    DP_API_ADD(pause),
    DP_API_ADD(quit),
    DP_API_ADD(list),
    DP_API_ADD(add),
    DP_API_ADD(remove)

};

struct DPSource {

    int address;
    int port;
    char* api;
    // type : real-time or batch
    // min_interval : how often to get data

} DPSource;

#endif