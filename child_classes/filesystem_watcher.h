#ifndef FILESYSTEM_WATCHER_H
#define FILESYSTEM_WATCHER_H
#include <sys/types.h>
#include <sys/inotify.h>
#include <stdio.h>
#include <limits.h>
#include <unistd.h> 
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <cstring>
#include "base_classes/sender_background_service.h"
#define MAX_EVENTS 1024
#define NAME_LEN 32
#define EVENT_SIZE (sizeof(struct inotify_event))
#define BUF_LEN (MAX_EVENTS * (EVENT_SIZE + NAME_LEN))
class FilesystemWatcher: public SenderBackgroundService<double>
{
	void run() override;	
        bool validatefile(char *);
        void sendfile(char *);
};
#endif
