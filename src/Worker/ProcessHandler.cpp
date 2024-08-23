#include <vector>

#include "ProcessHandler.hpp"
#include "UI/ConverterFrame.hpp"

using namespace std;

void ProcessHandler::runProcessThread(const ProcessInfo &info) {
    ProcessHandler handler(info);
    handler.run();
}


#ifdef I2V_WINDOWS

#else
void ProcessHandler::run() {
    //Construct arguments
    const string ip = "tcp://localhost:" + to_string(info.port);
    const char* args[] = {
        "ffmpeg", "-y",
        "-framerate", to_string(info.fps).c_str(),
        "-i", info.input.ToUTF8().data(),
        "-vcodec", "libx264",
        "-pix_fmt", "yuv420p",
        "-r", to_string(info.fps).c_str(),
        info.output.ToUTF8().data(),
        "-progress", ip.c_str(),
        nullptr
    };

    /*const char* test[12] = {
        info.exeLocation.c_str(), "-y",
        "-r", str.str().c_str(),
        "-i", info.input.c_str(),
        "-vcodec", "libx264",
        "-pix_fmt", "yuv420p",
        info.output.c_str(),
        NULL
    };*/

    childPid = fork();

    if (childPid == 0) {
        execvp("ffmpeg", const_cast<char **>(args));
    }

    int status;
    waitpid(childPid, &status, 0);

    bool success = false;
    if (WIFEXITED(status)) {
        success = WEXITSTATUS(status) == 0;
    }

    if (success) info.frame->reportSuccess();
    else info.frame->reportError();
}

#endif