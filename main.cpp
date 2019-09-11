#include <signal.h>
#include "child_classes/network_client.h"
#include "child_classes/filesystem_watcher.h"
#include <QCoreApplication>
volatile sig_atomic_t flag = 1;
void ctrlc(int sig)
{
    std::cout << "Ctrl-C pressed. Exiting" << std::endl;
    flag = 0;
    exit(0);
}
int main(int argv, char * argc[])
{
    QCoreApplication app(argv, argc);
    signal(SIGINT, ctrlc); 
    FilesystemWatcher watcher;
    NetworkClient client;
    watcher.addListener(&client);
    std::cout << "start" << std::endl;
    //client.start();
    watcher.start();
    std::cout << "end" << std::endl;
    //watcher.send(1.0);
    while(flag);
    std::cout << "stopping watcher" << std::endl;
   //watcher.stop();
   return app.exec();
}
