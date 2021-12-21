# Proof-of-Concept Data Pipeline Server

## **Problem Description**

### **Objectives**

To build a data pipeline server, a client, and an external data source server for proof of concept purpose to demonstrate the communication between threads in a process as well as the communication between processes (socket/WebSocket):

### **Specifications**

- Implementing the above three main components in C/C++ on **Linux** (code can be either pushed to **Github** or compress a zip file through email).
- The **data pipeline server** should have **multiple workers (threads)**. Each work does a dedicated job and communicate with the other workers **through either pipe, named pipe, message queue, shared memory, TCP socket, Unix domain socket, or ZeroMQ**.
- Use either **TCP socket or WebSocket to communicate between the data pipeline server and the client**.
- Use either **TCP socket, WebSocket or Rest API to communicate between the external data source server and the data pipeline server**.
- Imagining the **external data source servers could/will have  multiple different types**. Meaning, more and **more external data connector client can be added as needed** and **the "Data Writer" worker as its name suggested, it serves as a centralized data writer that will collect the data from the external data connectors and write data into the message queue.**
- **Ping/pong heartbeat** to ensure the peer is still alive.
- **Timeout handling**
- Note: Try to implement as many above items as you can.
- Deadline: Three weeks.

## **Solution Design**

### **What is a Data Pipeline**
Arbitrary steps to move data from the source system to the target system. If configured and managed astutely, it can give the clients access to consistent and well-structured datasets for analysis. Often times it is used to consolidate information from numerous sources for systematizing data transfer and transformation

### **Data Source Server**
For the purposes of this project, the data source server will load a file formatted .csv or .json at startup and respond to queries from its clients

https://github.com/paul-m-kim/poc_data_pipeline_source

### **Data Pipeline Server**
At initialization, the server waits for a client connection.

Once a client connects, the client can add data sources through the Custom Data Pipeline API.

*Types of data sources*
-  Real-time data
    - Connection protocol: TCP Sockets
    - Persistent connection
    - websockets adds complexity and support for it is not currently widespread
-  Batch data
    - Connection protocol: TCP Sockets
    - Using REST API (non-persistent / stateless connection)

Each time a data is queried/received, it is put into the message queue and sent to the client.

### **Client**
Simple TCP socket client that communicates with the Data Pipline Server via a Custom API.

https://github.com/paul-m-kim/poc_data_pipeline_client
## **Development Environment Setup**
### Setting up the Unix Environment ###

1. Update the unix system with the following command
```bash
$ sudo apt update && sudo apt upgrade -y
```
2. in the terminal enter the following command to install the compiler, standard libraries, and debug tools (toolchain)
```bash
$ sudo apt install build-essentials
```
### Setting up VS Code

1. My editor of choice was VS Code
```bash
$ sudo apt install code
```
2. Open up this repository with code by
```bash
$ cd /directory/to/repository
$ code .
```

3. Install recommended C/C++ extensions
4. Be sure to install ` Makefile Tools ` extension to make VS Code the frontend for building and debugging the code
5. With Makefile Tools installed, type `Ctrl + P` to access its funtions
6. To build all, type into the prompt `Makefile: build target ALL`
7. To debug, type into the prompt `Makefile: Debug the selected binary target`

## **Building**

### Makefile

*Targets*
- all

- test

### CMake
*wip*
