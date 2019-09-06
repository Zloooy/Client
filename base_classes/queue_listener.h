#ifndef QUEUE_LISTENER_H
#define QUEUE_LISTENER_H
#include "listener.h"
#include <queue>
#include <iostream>
template <typename msgtype>
class QueueListener: public Listener<msgtype>
{
    protected:
        std::queue<msgtype> msg_queue;
    public:
        void recieve(msgtype) override;
	void clear() override;
};
template<typename msgtype>
void QueueListener<msgtype>::recieve(msgtype msg)
{
    msg_queue.push(msg);
}
template<typename msgtype>
void QueueListener<msgtype>::clear()
{
	std::queue<msgtype> q;
	std::swap(msg_queue, q);
}
#endif
