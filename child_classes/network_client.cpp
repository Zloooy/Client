#include "network_client.h"
NetworkClient::NetworkClient(const char* addr, int port):
    port(htons(port))
{
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(addr);
    std::cout << serv_addr.sin_addr.s_addr << std::endl;
    serv_addr.sin_port = htons(port);
    sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock < 0)
    {
        perror("[Error]");
    }
}
NetworkClient::NetworkClient():
    NetworkClient("127.0.0.1", 8081)
{}
NetworkClient::~NetworkClient()
{
    close(sock);
}
void NetworkClient::recieve(double d)
{
    std::cout << "recieved" << d << std::endl;
    double_bytes dbytes;
    dbytes.d = d;
    int sent_size = sendto(sock, dbytes.bytes, sizeof(dbytes), 0, (struct sockaddr*) &serv_addr, sizeof(serv_addr)); 
    if (sent_size < 0)
    {
        perror("[Error]");
    }
    else std::cout << sent_size << std::endl;
}
void NetworkClient::clear(){}
/*void NetworkClient::run()
{
    //std::cout << "Created socket "  << sock << std::endl;
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
}*/
