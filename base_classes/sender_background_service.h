#ifndef SENDER_BACKGROUND_SERVICE_H
#define SENDER_BACKGROUND_SERVICE_H
#include "sender.h"
#include "background_service.h"
#include <mutex>
template <typename msgtype>
class SenderBackgroundService: public Sender<msgtype>, public BackgroundService
{
	std::mutex listeners_mutex;
	public:
            void addListener(Listener<msgtype> *) override;
	    void clear_listeners() override;
	protected:
            void send(msgtype) override;
};
template<typename msgtype>
void SenderBackgroundService<msgtype>::addListener(Listener<msgtype> * listener)
{
	std::unique_lock<std::mutex> lock(listeners_mutex);
	Sender<msgtype>::addListener(listener);
}
template<typename msgtype>
void SenderBackgroundService<msgtype>::send(msgtype msg)
{
	std::unique_lock<std::mutex> lock(listeners_mutex);
	Sender<msgtype>::send(msg);
}
template<typename msgtype>
void SenderBackgroundService<msgtype>::clear_listeners()
{
	std::unique_lock<std::mutex> lock (listeners_mutex);
	Sender<msgtype>::clear_listeners();
}
#endif
