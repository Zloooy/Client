#include "filesystem_watcher.h"
void FilesystemWatcher::run()
{
    std::cout << "running" << std::endl;
    DIR * dir = opendir(".");
    char buf[BUF_LEN];
    int watcher_descriptor  = 0, event_count, inotify_descriptor = inotify_init();
    struct dirent * current_file;
    while((current_file = readdir(dir)) != NULL)
            {
                std::cout << current_file -> d_name << std::endl;
                if (validatefile(current_file -> d_name))
                {
                    sendfile(current_file -> d_name);
                }
                else std::cout << "Wrong file" << std::endl;
            }
    if (inotify_descriptor < 0) throw "Can't create fd!";
    std::cout << "Created fd" << std::endl;
    watcher_descriptor = inotify_add_watch(inotify_descriptor, ".", IN_CREATE | IN_MODIFY);
    if (watcher_descriptor < 0) throw "Can't create wd!";
    std::cout << "Created wd" << std::endl;
    while(isRunning())
    {
        std::cout << "Running" << std::endl;
        event_count = read(inotify_descriptor, buf, BUF_LEN);
        if (event_count < 0) throw "Failed to read events";
        inotify_event * event = (struct inotify_event*) (&buf[0]);
        for ( int  i = 0;  i < event_count; i += EVENT_SIZE + event -> len)
        {
            if (!(event -> mask & IN_ISDIR) && ((event -> mask & IN_CREATE) | (event -> mask & IN_MODIFY)))
            {
            if (validatefile(event -> name))
                {
                std::cout << event -> name << std::endl; 
                sendfile(event -> name);
                }
            }
            event = (struct inotify_event*) (&buf[i]);
        }
    }
    inotify_rm_watch(inotify_descriptor, watcher_descriptor);
    close(inotify_descriptor);
}
void FilesystemWatcher::sendfile(char * filename)
{
    double double_buf;
    std::ifstream file;
    file.open(filename);
    while(file>>double_buf) send(double_buf);
    file.close();
}
bool FilesystemWatcher::validatefile(char * filename)
{
    char * extension = strchr(filename, '.');
    if (extension == NULL) return false;
    std::cout << filename << " has extension '" << extension <<"'" << std::endl;
    return strcmp(extension, ".mat") == 0;
}
