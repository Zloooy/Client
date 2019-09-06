#ifndef SENDER_H
#define SENDER_H
#include<vector>
#include "listener.h"
template <typename frommsgtype, typename tomsgtype>
class Pipe;
template <typename msgtype>
class Sender
{
	std::vector<Listener<msgtype>*> listeners;
	public:
	virtual void send(msgtype);
	virtual void clear_listeners();
	virtual void addListener(Listener<msgtype>*);
	template<typename tomsgtype, typename ... Listeners>
        void addListenerChain(Pipe<msgtype, tomsgtype>*, Listeners ...);
        void addListenerChain(Listener<msgtype>*);
};
template<typename msgtype>
void Sender<msgtype>::addListener(Listener<msgtype> * listener)
{
    listeners.push_back(listener);
}
template<typename msgtype>
void Sender<msgtype>::send(msgtype msg)
{
    typename std::vector<Listener<msgtype>*>::iterator it = listeners.begin(); 
    for(; it != listeners.end(); it++)
    {
        (*it) -> recieve(msg);
    }
}
template <typename msgtype>
void Sender<msgtype>::clear_listeners()
{
    typename std::vector<Listener<msgtype>*>::iterator it = listeners.begin(); 
    for(; it != listeners.end(); it++)
    {
        (*it) -> clear();
    }
}
template <typename msgtype>
template<typename tomsgtype, typename ... Listeners>
void Sender<msgtype>::addListenerChain(Pipe<msgtype, tomsgtype>* pipe, Listeners ... listeners)
{
    Sender<msgtype>::addListener(pipe);
    pipe -> addListenerChain(listeners ...);
}
template<typename msgtype>
void Sender<msgtype>::addListenerChain(Listener<msgtype>* listener)
{
    addListener(listener);
}
#endif
