#include "background_service.h"
void BackgroundService::start()
{
    running = ATOMIC_VAR_INIT(true);
    thread = new std::thread(&BackgroundService::run, this);
}
void BackgroundService::stop()
{
    running = ATOMIC_VAR_INIT(false);
    thread -> join();
    delete thread;
}
