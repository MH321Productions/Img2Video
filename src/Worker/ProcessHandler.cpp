#include <filesystem>
#include <regex>

#include "ProcessHandler.hpp"
#include "UI/ConverterFrame.hpp"

using namespace std;
using namespace std::filesystem;

const wxString queryErrorHeader = "Couldn't query the total frame number:\n";
const wxString runErrorHeader = "Couldn't run FFmpeg:\n";


void ProcessHandler::startConversion(const ProcessInfo &processInfo) {
    this->info = processInfo;
    aborted = false;
    running = true;

    cout << "Query frames" << endl;
    int frameCount = queryFrameCountInternally();
    if (frameCount == -1) {
        frame->reportError(msg);
        return;
    }
    else frame->setTotalFrameCount(frameCount);

    cout << "Running ffmpeg" << endl;
    bool started = startFFmpeg();
    if (!started) frame->reportError(msg);
    else {
        readerThread = thread(runWorkerThread, this);
        readerThread.detach();
    }
}

bool ProcessHandler::abortConversion() {
    scoped_lock lock(mtxRunning);

    if (!running) return false;
    aborted = true;

    terminateFFmpeg();

    return true;
}

bool ProcessHandler::runError(const wxString &errorMsg) {
    msg = runErrorHeader + errorMsg;
    return false;
}

int ProcessHandler::queryFrameCountInternally() const {
    path file(info.input.ToUTF8().data());
    path format = file.extension();
    path dir = file.parent_path();
    int frameCount = 0;
    regex rx("^\\d{4}" + format.string());

    for (const directory_entry& entry: directory_iterator(dir)) {
        if (regex_match(entry.path().filename().string(), rx)) frameCount++;
    }

    return frameCount;
}

void ProcessHandler::processLine(const string& line) {
    auto [key, value] = splitLine(line);

    if (key == "frame") frameNumber = stoi(value);
    else if (key == "speed" && value != "N/A") speed = stod(value.substr(0, value.size() - 1));
    else if (key == "progress") frame->setConversionStatus(frameNumber, speed);
}

pair<string, string> ProcessHandler::splitLine(const string &line) {
    size_t index = line.find('=');
    if (index == string::npos) return {line, ""};
    else return {line.substr(0, index), line.substr(index + 1)};
}


