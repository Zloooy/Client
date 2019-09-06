#ifndef NETWORK_CLIENT_H
#define NETWORK_CLIENT_H
//#include <sys/types.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
#include <iostream>
//#include <cstring>
#include <QDataStream>
#include <QUdpSocket>
#include <QHostAddress>
#include "base_classes/queue_listener_background_service.h"
class NetworkClient: public QueueListenerBackgroundService<double>
{
    typedef union {
        double d;
        char bytes[sizeof(double)];
    } double_bytes;
    QUdpSocket *sock = NULL;
    QHostAddress addr;
    int port;
    void process(double) override;
    void run() override;
    public:
        NetworkClient(QHostAddress, int);
        NetworkClient();
};
#endif
