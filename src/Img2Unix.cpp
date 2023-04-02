#ifndef I2V_WINDOWS

#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <wait.h>

#include "Img2Video.hpp"

using namespace std;

static const char* whichArgs[3] = {"/usr/bin/which", "ffmpeg", NULL};

namespace Img2Video {

    bool checkInstall(ConversionInfo& info) {
        int fd[2];
        if (pipe(fd) == -1) {
            cerr << "Error while checking FFMpeg: Couldn't open pipe: " << strerror(errno) << endl;
            return false;
        }

        pid_t id = fork();
        if (id == -1) {
            cerr << "Error while checking FFMpeg: Couldn't open child process: " << strerror(errno) << endl;
            return false;
        } else if (id == 0) { //Child process: run which ffmpeg
            close(fd[0]);
            dup2(fd[1], 1);

            execv("/usr/bin/which", (char**) whichArgs);
        }

        //Parent process
        close(fd[1]);

        int status, retCode = 0;
        if (waitpid(id, &status, 0) == -1) {
            cerr << "Error while checking FFMpeg: Couldn't wait for child process: " << strerror(errno) << endl;
            return false;
        }

        if (WIFEXITED(status)) retCode = WEXITSTATUS(status);

        string res = "";
        char buf[128];
        int numRead;

        while ((numRead = read(fd[0], buf, 128)) > 0) {
            res.append(buf, numRead);
        }
        close(fd[0]);

        res.pop_back(); //Remove trailing \n
        info.exeLocation = res;

        return (retCode == 0 && !res.empty());
    }

    int runConversion(const ConversionInfo& info) {
        return 0;
    }
}

#endif //I2V_WINDOWS