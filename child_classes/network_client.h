#ifndef NETWORK_CLIENT_H
#define NETWORK_CLIENT_H
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>
#include "base_classes/queue_listener_background_service.h"
class NetworkClient: public Listener<double>
{
    typedef union {
        double d;
        char bytes[sizeof(double)];
    } double_bytes;
	sockaddr_in serv_addr;
    int sock, port;
    void recieve(double) override;
	void clear();
    public:
        NetworkClient(const char*, int);
        NetworkClient();
	~NetworkClient();
};
#endif
