#ifndef BACKGROUND_SERVICE_H
#define BACKGROUND_SERVICE_H
#include <thread>
#include <atomic>
class BackgroundService
{
    std::atomic_bool running = ATOMIC_VAR_INIT(false);
    protected:
        std::thread * thread;
        virtual void run() = 0;
    public:
        virtual void start();
        virtual void stop();
        virtual bool isRunning() final
        {
            return running;
        }
};
#endif
