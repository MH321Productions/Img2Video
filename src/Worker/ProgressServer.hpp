#ifndef PROGRESSSERVER_HPP
#define PROGRESSSERVER_HPP

#include <wx/socket.h>

class ConverterFrame;

class ProgressServer {
    public:
        static void runServerThread(ConverterFrame* frame);

        int getPort() const {return port;}

    private:
        ConverterFrame* frame;
        int port = -1;
        wxIPV4address address;
        wxSocketServer* server;

        explicit ProgressServer(ConverterFrame* frame);
        ~ProgressServer();

        void run();
};

#endif //PROGRESSSERVER_HPP
