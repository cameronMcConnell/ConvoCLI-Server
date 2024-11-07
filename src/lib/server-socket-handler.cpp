#include "headers/server-socket-handler.hpp"

ServerSocketHandler::ServerSocketHandler(int portNumber) {
    if ((this->serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        // handle error here.
    }
    
    this->serverAddress.sin_family = AF_INET;
    this->serverAddress.sin_port = htons(portNumber);
    this->serverAddress.sin_addr.s_addr = INADDR_ANY;
    
    if (bind(this->serverSocket, (struct sockaddr *)&this->serverAddress, sizeof(this->serverAddress)) < 0) {
        // handle error here.
        close(this->serverSocket);
    }
    
    if (listen(this->serverSocket, 10) < 0) {
        // handle error here.
        close(this->serverSocket);
    }

    std::cout << "Server listening on port " << portNumber << std::endl;
}

void ServerSocketHandler::start() {
    // create thread for main accept client loop
    std::thread acceptClientsThread(acceptClients);

    
}

void ServerSocketHandler::stop() {
    // kill main thread and close socket
}

void ServerSocketHandler::acceptClients() {
    std::mutex acceptClientsMutex;

    while (true) {
        int clientSocket;
        
        if ((clientSocket = accept(this->serverSocket, nullptr, nullptr)) != -1) {
            acceptClientsMutex.lock();
            
            this->clients.insert(clientSocket);

            acceptClientsMutex.unlock();
        }
    }
}