#ifndef LISTENER_H
#define LISTENER_H
template<typename msgtype>
class Listener
{
	public:
		virtual void recieve(msgtype) = 0;
		virtual void clear() = 0;
};
#endif
