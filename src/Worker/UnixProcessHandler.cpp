#ifndef I2V_WINDOWS

#include <string>
#include <sys/wait.h>
#include <ext/stdio_filebuf.h>

#include "ProcessHandler.hpp"
#include "UI/ConverterFrame.hpp"

using namespace std;

wxString errorString(const wxString& msg) {
    return wxString::Format("%s: %s", msg, strerror(errno));
}

bool ProcessHandler::startFFmpeg() {
    //Construct arguments
    const char* args[] = {
        "ffmpeg", "-y",
        "-framerate", info.fps.ToUTF8().data(),
        "-i", info.input.ToUTF8().data(),
        "-r", info.fps.ToUTF8().data(),
        "-vcodec", "libx264",
        "-pix_fmt", "yuv420p",
        info.output.ToUTF8().data(),
        "-progress", "-",
        nullptr
    };

    //Construct pipe
    if (pipe(fd) == -1) return runError(errorString("Couldn't create pipe"));

    childPid = fork();
    if (childPid == -1) return runError(errorString("Couldn't fork"));
    if (childPid == 0) {
        //Set pipe as stdout
        close(fd[0]);
        dup2(fd[1], 1);
        execvp("ffmpeg", const_cast<char **>(args));
    }

    //Parent process
    close(fd[1]);

    return true;
}

void ProcessHandler::runWorkerThread(ProcessHandler *handler) {
    //Read from pipe
    __gnu_cxx::stdio_filebuf<char> filebuf(handler->fd[0], ios::in);
    istream in(&filebuf);
    string line;

    while (getline(in, line)) handler->processLine(line);

    int status;
    waitpid(handler->childPid, &status, 0);

    scoped_lock lock(handler->mtxRunning);
    handler->running = false;

    int retCode = WIFEXITED(status) ? WEXITSTATUS(status) : -1;

    if (handler->aborted) return;
    else if (retCode == 0) handler->frame->reportSuccess();
    else handler->frame->reportError(wxString::Format("ffmpeg exited with return code %d", retCode));
}

void ProcessHandler::terminateFFmpeg() {
    kill(childPid, SIGTERM);
}

#endif