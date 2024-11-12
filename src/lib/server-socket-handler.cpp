#include "headers/server-socket-handler.hpp"

ServerSocketHandler::ServerSocketHandler(int portNumber) {
    if ((this->serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        // Throw error here.
    }
    
    this->serverAddress.sin_family = AF_INET;
    this->serverAddress.sin_port = htons(portNumber);
    this->serverAddress.sin_addr.s_addr = INADDR_ANY;
    
    if (bind(this->serverSocket, (struct sockaddr *)&this->serverAddress, sizeof(this->serverAddress)) < 0) {
        // Throw error here.
        close(this->serverSocket);

    }
    
    if (listen(this->serverSocket, 10) < 0) {
        // Throw error here.
        close(this->serverSocket);
    }

    this->serverIsActive = true;

    std::cout << "Server listening on port " << portNumber << "." << std::endl;
}

void ServerSocketHandler::start() {
    std::thread acceptClientsThread(&ServerSocketHandler::acceptClients, this);

    while (this->serverIsActive) {
        char buffer[1024];

        std::unique_lock<std::mutex> lock(this->clientMutex);

        for (int clientSocket : this->clients) {
            ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);

            if (bytesRead > 0) {
                ServerSocketHandler::propogateMessage(clientSocket, buffer);
            }
            else if (bytesRead == 0 || (bytesRead == -1 && errno != EAGAIN)) {
                close(clientSocket);
                this->clients.erase(clientSocket);
                
            }
        }
    }

    if (acceptClientsThread.joinable()) {
        acceptClientsThread.join();
    }
}

void ServerSocketHandler::stop() {
    this->serverIsActive = false;
}

void ServerSocketHandler::acceptClients() {
    while (this->serverIsActive) {
        int clientSocket;
        
        if ((clientSocket = accept(this->serverSocket, nullptr, nullptr)) != -1) {
            std::unique_lock<std::mutex> lock(this->clientMutex);
            
            this->clients.insert(clientSocket);

            lock.unlock();
        } 
        else if (errno != EAGAIN && errno != EWOULDBLOCK) {
            // Throw error here.
        }
    }
}

void ServerSocketHandler::propogateMessage(int sendingClientSocket, char* message) {
    for (int clientSocket : this->clients) {
        if (clientSocket != sendingClientSocket) {
            ssize_t bytesSent = send(clientSocket, message, sizeof(message), 0);

            if (bytesSent == -1) {
                // Handle error here.
            }
        }
    }
}