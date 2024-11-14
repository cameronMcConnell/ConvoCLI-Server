//#########################################################################

#include "lib/headers/server.hpp"
#include <string>
#include <csignal>

int parsePortNumber(int argc, char* argv[]);
void handleExit(int signal);

Server* server;

//#########################################################################

int main(int argc, char* argv[]) {
    int portNumber;

    if ((portNumber = parsePortNumber(argc, argv)) == -1) {
        return 1;
    }

    std::signal(SIGINT, handleExit);
    
    server = new Server(portNumber);

    server->start();

    return 0;
}

int parsePortNumber(int argc, char* argv[]) {
    if (argc != 2) {
        return -1;
    }

    // implement error handling here at some point
    return std::stoi(argv[1]);
}

void handleExit(int signal) {
    server->stop();
    delete server;
    exit(signal);
}