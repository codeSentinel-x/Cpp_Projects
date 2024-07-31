#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <thread>
#include <vector>

void ReceiveMessage(int sock);
int main(){
    int sock = 0;
    int readFromServer;
    struct sockaddr_in serverAddress;
    std::string name;
    std::cout << "Enter your name" << std::endl;
    system("clear");
    getline(std::cin, name);

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
      std::cout << "\n Socket creation error \n";
      return -1;
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);

    if (inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr) <= 0){
        std::cout << "\nInvalid address/ Address not supported \n";
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0){
        std::cout << "\nConnection Failed \n";
        return -1;
    }

    std::string message;
    std::thread receiver(ReceiveMessage, sock);
    while (true){
        // std::cout << "Enter message: ";
        std::getline(std::cin, message);

        if (message == "exit"){
            break;
        }
        message = name + ": " + message;
        send(sock, message.c_str(), message.length(), 0);
    }
    receiver.detach();
    close(sock);
    return 0;
}

void ReceiveMessage(int sock){
    char buffer[2048] = {0};
    while (true) {
        memset(buffer, 0, sizeof(buffer)); 
        int valRead = read(sock, buffer, sizeof(buffer));
        if (valRead > 0) {
            std::cout << buffer << std::endl;
        }
    }
}
