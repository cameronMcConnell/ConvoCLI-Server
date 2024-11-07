#include <string>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> 
#include <unordered_set>
#include <thread>
#include <mutex>

using set = std::unordered_set<int>;

class ServerSocketHandler {
    private:
        int serverSocket;
        sockaddr_in serverAddress;
        set clients;

        void acceptClients();

    public:
        ServerSocketHandler(int portNumber);
        void start();
        void stop();
};