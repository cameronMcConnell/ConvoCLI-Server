#include <string>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> 
#include <unordered_set>
#include <thread>
#include <mutex>

class Server {
    public:
        Server(int portNumber);
        void start();
        void stop();
    
    private:
        void handleAcceptingClients();
        void propogateMessage(int sendingClientSocket, char* message);

        int serverSocket;
        sockaddr_in serverAddress;
        bool serverIsActive;
        std::unordered_set<int> clients;
        std::mutex clientMutex;
};