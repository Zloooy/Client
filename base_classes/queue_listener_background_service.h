#ifndef QUEUE_LISTENER_BACKGROUND_SERVICE_H
#define QUEUE_LISTENER_BACKGROUND_SERVICE_H
#include "base_classes/background_service.h"
#include "base_classes/queue_listener.h"
#include <condition_variable>
template <typename msgtype>
class QueueListenerBackgroundService: public BackgroundService, public QueueListener<msgtype>
{
    std::condition_variable wait4data;
    std::mutex msg_queue_mutex;
    public:
    void recieve(msgtype) override;
    void stop() override;
    protected:
    void run() override;
    virtual void process(msgtype) = 0;
};
template<typename msgtype>
void QueueListenerBackgroundService<msgtype>::run()
{
    msgtype msg;
    while(isRunning())
    {
        {
            std::unique_lock<std::mutex> lock(msg_queue_mutex);
            while(QueueListener<msgtype>::msg_queue.empty() && isRunning())
            {
                wait4data.wait(lock);
                if (QueueListener<msgtype>::msg_queue.empty()){
                    std::cout << "no more data in queue_listener_background_service. Stopping." << std::endl;
                    return; 
                }
            }
            msg = QueueListener<msgtype>::msg_queue.front();
            QueueListener<msgtype>::msg_queue.pop();
        }
        process(msg);
    }
}
template <typename msgtype>
void QueueListenerBackgroundService<msgtype>::recieve(msgtype msg)
{
    std::unique_lock<std::mutex> msg_queue_lock;
    QueueListener<msgtype>::recieve(msg);
    wait4data.notify_one();
}
template <typename msgtype>
void QueueListenerBackgroundService<msgtype>::stop()
{
    wait4data.notify_one();
    BackgroundService::stop();
}
#endif
