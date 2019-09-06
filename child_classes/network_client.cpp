#include "network_client.h"
NetworkClient::NetworkClient(QHostAddress addr, int port):
    addr(addr),
    port(port)
{}
NetworkClient::NetworkClient()
{
    NetworkClient(QHostAddress::LocalHost, 8081);
}
void NetworkClient::run()
{
    sock = new QUdpSocket;
    //std::cout << "Created socket "  << sock << std::endl;
    QueueListenerBackgroundService<double>::run();
}
void NetworkClient::process(double d)
{
    std::cout << "processing " << d << std::endl;
    double_bytes dbytes;
    dbytes.d = d;
    char * arr = dbytes.bytes;
    QByteArray datagram(arr, sizeof(double_bytes)); 
    std::cout << datagram.data() << std::endl;
    QDataStream out(&datagram, QIODevice::WriteOnly);
    for (int i = 0; i < sizeof(double_bytes); i++)
    {
        out << dbytes.bytes[i];
    }
    out << dbytes.d;
    out.setVersion(QDataStream::Qt_5_13);
    sock -> writeDatagram(datagram, addr, port);
}
