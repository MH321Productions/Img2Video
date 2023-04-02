#include <iostream>
#include <sstream>

#include "Img2Video.hpp"

using namespace std;

enum ParseMode : uint8_t {Input, FPS, Output};

void showHelpString();
void showVersionString();

int main(int argc, char* argv[]) {
    //Parse arguments
    if (argc < 2) {
        cerr << "No input specified" << endl;
        return 1;
    }

    vector<string> args(argc - 1);
    for (int i = 0; i < argc - 1; i++) args.at(i) = argv[i + 1];

    bool showHelp = false;
    bool showVersion = false;
    bool hasFps = false;
    bool hasOutput = false;
    bool hasInput = false;
    ParseMode mode = Input;
    istringstream str;
    Img2Video::ConversionInfo info;
    for (int i = 0; i < args.size(); i++) {
        if (args.at(i) == "-h" || args.at(i) == "--help") {
            showHelp = true;
            break;
        } else if (args.at(i) == "-v" || args.at(i) == "--version") {
            showVersion = true;
            break;
        } else if (args.at(i) == "-fps") {
            if (hasFps) {
                cerr << "FPS already specified as " << info.fps << endl;
                return 1;
            } else if (mode == Output) {
                cerr << "No output specified after -o" << endl;
                return 1;
            }
            mode = FPS;
        } else if (args.at(i) == "-o") {
            if (hasOutput) {
                cerr << "Output already specified as \"" << info.output << '\"' << endl;
                return 1;
            } else if (mode == FPS) {
                cerr << "No fps specified after -fps" << endl;
                return 1;
            }
            mode = Output;
        } else if (args.at(i).at(0) == '-') {
            cerr << "Unrecognized option \"" << args.at(i) << "\"" << endl;
            return 1;
        } else {
            switch (mode) {
                case Input:
                    if (hasInput) {
                        cerr << "Input already specified as \"" << info.input << '\"' << endl;
                        return 1;
                    }

                    info.input = args.at(i);
                    hasInput = true;
                    break;
                
                case FPS:
                    str.str(args.at(i));
                    str >> info.fps;
                    str.clear();

                    if (info.fps <= 0) {
                        cout << "Invalid fps value (or couldn't decode it)" << endl;
                        return 1;
                    }

                    hasFps = true;
                    mode = Input;
                    break;
                
                case Output:
                    info.output = args.at(i);
                    hasOutput = true;
                    mode = Input;
                    break;
            }
        }
    }

    //Check parsed inputs
    if (showHelp) {
        showHelpString();
        return 0;
    } else if (showVersion) {
        showVersionString();
        return 0;
    } else if (!hasInput) {
        cerr << "No input specified" << endl;
        return 1;
    }

    if (!hasOutput) info.output = "Video.mp4";
    if (!hasFps) info.fps = 25;

    if (!Img2Video::checkInstall(info)) {
        cerr << "FFMpeg is not installed on this system or cannot be found" << endl;
        return 1;
    }

    return Img2Video::runConversion(info);
}

void showHelpString() {
    cout << "img2video - A minimal FFMpeg wrapper to convert images to an x264 video" << endl;
    cout << "Usage: img2video [options...] <file pattern>" << endl;
    cout << "Options:" << endl;
    cout << "  -h, --help\tDisplay this information" << endl;
    cout << "  -fps\t\tChange the frame rate (can be decimal, 25 is the standard)" << endl;
    cout << "  -o\t\tChange the output file (Video.mp4 is the standard)" << endl;
    cout << "  -v, --version\tShow the version information" << endl;
}

void showVersionString() {
    cout << "img2video version " << Img2Video::majorVersion << '.' << Img2Video::minorVersion << '.' << Img2Video::patchVersion << endl;
}
