#include <iostream>

#include <wx/txtstrm.h>
#include <wx/sckstrm.h>
#include <wx/wfstream.h>

#include "ProgressServer.hpp"

#include <wx/any.h>

#include "UI/ConverterFrame.hpp"

using namespace std;

void ProgressServer::runServerThread(ConverterFrame* frame) {
    ProgressServer server(frame);
    server.run();
}

ProgressServer::ProgressServer(ConverterFrame *frame) : frame(frame), server(nullptr) {
    cout << boolalpha << address.AnyAddress() << endl;
    cout << address.Service(8080) << endl;
    port = address.Service();

    std::cout << address.IPAddress().ToUTF8().data() << ":" << address.Service() << std::endl;
}

ProgressServer::~ProgressServer() {
    delete server;
}

void ProgressServer::run() {
    server = new wxSocketServer(address);
    cout << server->IsOk() << endl; //Test

    cout << "Server ready for connection" << endl;

    wxSocketBase* conn = server->Accept();
    wxSocketInputStream socket_input_stream(*conn);
    wxTextInputStream input(socket_input_stream);
    wxString line;
    wxString frameNumString;
    int frameNum;

    cout << "Connection established" << endl;

    while (!(line = input.ReadLine()).empty()) {
        if (line.StartsWith("frame=", &frameNumString)) {
            cout << frameNumString << endl;
            frameNumString.ToInt(&frameNum);
            frame->setFrameNumber(frameNum);
        }
    }

    conn->Close();
    server->Close();
    cout << "Server closed" << endl;
}
