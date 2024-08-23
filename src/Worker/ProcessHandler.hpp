#ifndef PROCESSHANDLER_HPP
#define PROCESSHANDLER_HPP

#include <wx/string.h>

#ifdef I2V_WINDOWS

#else
#include <unistd.h>
#include <sys/wait.h>
#endif

class ConverterFrame;

struct ProcessInfo {
    ConverterFrame* frame;
    wxString input;
    wxString output;
    int fps;
    int port;
};

class ProcessHandler {
    public:
        static void runProcessThread(const ProcessInfo& info);

    private:
        explicit ProcessHandler(const ProcessInfo& info) : info(info) {}

        void run();

        ProcessInfo info;

#ifdef I2V_WINDOWS

#else
        pid_t childPid = -1;
#endif
};


#endif //PROCESSHANDLER_HPP
