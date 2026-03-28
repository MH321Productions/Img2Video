#ifdef I2V_WINDOWS

#include "ProcessHandler.hpp"
#include "UI/ConverterFrame.hpp"

using namespace std;

bool ProcessHandler::startFFmpeg() {
    //Construct arguments
    wxString args = "ffmpeg -y";
    args << " -framerate " << info.fps
         << " -i \"" << info.input << '\"'
         << " -r " << info.fps
         << " -vcodec libx264"
         << " -pix_fmt yuv420p"
         << " \"" << info.output << "\""
         << " -progress -";


    //Setup pipe and process
    HANDLE pipeChildWrite;
    SECURITY_ATTRIBUTES sa {
            sizeof(SECURITY_ATTRIBUTES),
            nullptr,
            true
    };

    if (!CreatePipe(&pipeParentRead, &pipeChildWrite, &sa, 0)) return runError("Couldn't create pipe");
    if (!SetHandleInformation(pipeParentRead, HANDLE_FLAG_INHERIT, 0)) return runError("Couldn't configure pipe");

    STARTUPINFO si;

    ZeroMemory(&si, sizeof si);
    ZeroMemory(&pi, sizeof pi);

    si.cb = sizeof(si);
    si.hStdOutput = pipeChildWrite;
    si.hStdError = nullptr;
    si.hStdInput = nullptr;
    si.dwFlags |= STARTF_USESTDHANDLES;

    if (!CreateProcessW(
            nullptr,
            args.wchar_str(),
            nullptr,
            nullptr,
            true,
            CREATE_NO_WINDOW,
            nullptr,
            nullptr,
            &si,
            &pi
    )) {
        return runError("Couldn't start ffmpeg");
    }

    //Close child pipe
    CloseHandle(pipeChildWrite);

    return true;
}

void ProcessHandler::runWorkerThread(ProcessHandler* handler) {
    //Read from pipe
    const DWORD bufSize = 32;
    char buf[bufSize];
    vector<char> chars;
    vector<string> lines;
    DWORD readBytes;

    do {
        if (!ReadFile(
                handler->pipeParentRead, buf, bufSize, &readBytes, nullptr
        )) break;

        for (int i = 0; i < readBytes; i++) {
            chars.push_back(buf[i]);

            //Split into lines
            if (buf[i] == '\n') {
                string line = string(chars.data(), chars.size() - 1); //Construct string without \n
                lines.push_back(line);
                chars.clear();
            }
        }

        for (const string& line: lines) {
            cout << line << endl;
            handler->processLine(line);
        }
        lines.clear();

    } while (readBytes != 0);

    WaitForSingleObject(handler->pi.hProcess, INFINITE);

    scoped_lock lock(handler->mtxRunning);
    handler->running = false;

    DWORD retCode = -1;
    GetExitCodeProcess(handler->pi.hProcess, &retCode);

    CloseHandle(handler->pipeParentRead);
    CloseHandle(handler->pi.hProcess);
    CloseHandle(handler->pi.hThread);

    if (handler->aborted) return;
    else if (retCode == 0) handler->frame->reportSuccess();
    else handler->frame->reportError(wxString::Format("ffmpeg exited with return code %d", retCode));
}

void ProcessHandler::terminateFFmpeg() {
    TerminateProcess(pi.hProcess, 1);
}

#endif