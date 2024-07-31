#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <thread>
#include <mutex>

using std::cout;
std::mutex mtx;
void HandleClient(int clientSocket, std::vector<int>* allClients);
int main(){
    system("clear");
    std::vector<int> allClients;
    int option = 1;
    int serverFD;
    struct sockaddr_in address;
    int addressLength = sizeof(address);

    if ((serverFD = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        perror("Error while creating socket");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(serverFD, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &option, sizeof(option))){
        perror("Error while attaching socket");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    
    if (bind(serverFD, (struct sockaddr *)&address, sizeof(address)) < 0){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(serverFD, 3) < 0){
        perror("listen");
        exit(EXIT_FAILURE);
    }
    std::vector<std::thread> threads;
    while (true){
        int newSocket;
        if ((newSocket = accept(serverFD, (struct sockaddr*)&address, (socklen_t*)&addressLength)) < 0){
            perror("accept");
            exit(EXIT_FAILURE);
        }
        allClients.push_back(newSocket);
        threads.push_back(std::thread(HandleClient, newSocket, &allClients));
    }

    for (auto& th : threads) {
            if (th.joinable()) {
                th.join();
            }
        }
    close(serverFD);
    return 0;
}

void HandleClient(int clientSocket, std::vector<int>* allClients){
    char buffer[2048] = { 0 };
    while (true){
        memset(buffer, 0, sizeof(buffer));
        int bytes_read = read(clientSocket, buffer, sizeof(buffer));
        if (bytes_read == 0) {
            std::cout << "Client"<< clientSocket << " disconnected"  << std::endl;
            break;
        }
        {
            std::lock_guard<std::mutex> lock(mtx);
            std::cout << "Client" << clientSocket << ": " << buffer << std::endl;
        }
        for (int client : *allClients){
            send(client, buffer, strlen(buffer), 0);
        }

        if (strcmp(buffer, "exit") == 0) {
            std::cout << "Exit command received. Closing connection." << std::endl;
            break;
        }
    }
    close(clientSocket);
}
