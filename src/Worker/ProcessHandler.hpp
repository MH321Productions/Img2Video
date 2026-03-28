#ifndef PROCESSHANDLER_HPP
#define PROCESSHANDLER_HPP

#include <thread>
#include <map>
#include <vector>
#include <mutex>
#include <wx/string.h>

#ifdef I2V_WINDOWS
#include <Windows.h>
#else
#include <unistd.h>
#endif

class ConverterFrame;

struct ProcessInfo {
    wxString input;
    wxString output;
    wxString fps;
};

class ProcessHandler {
    public:
        static void runWorkerThread(ProcessHandler* handler);

        explicit ProcessHandler(ConverterFrame* frame) : frame(frame), frameNumber(0), speed(0.0), aborted(false), running(false) {}

        void startConversion(const ProcessInfo& processInfo);
        bool abortConversion();

    private:
        //Main thread
        ConverterFrame* frame;
        ProcessInfo info;
        wxString msg;
        std::thread readerThread;
        bool running;
        bool aborted;
        std::mutex mtxRunning;

#ifdef I2V_WINDOWS
        HANDLE pipeParentRead = nullptr;
        PROCESS_INFORMATION pi {};
#else
        int fd[2] = {0, 0};
        pid_t childPid = -1;
#endif

        //Worker thread
        int frameNumber;
        double speed;

        int queryFrameCountInternally() const;
        bool startFFmpeg();
        void processLine(const std::string& line);
        void terminateFFmpeg();

        bool runError(const wxString& errorMsg);

        static std::pair<std::string, std::string> splitLine(const std::string& line);
};


#endif //PROCESSHANDLER_HPP
