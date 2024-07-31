#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main(){

    int sock = 0;
    int valRead;
    struct sockaddr_in serverAddress;

    char buffer[2048] = { 0 };

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
    while (true){
        std::cout << "Enter message (type 'exit' to close): ";
        std::getline(std::cin, message);

        if (message == "exit")
        {
            break;
        }

        send(sock, message.c_str(), message.length(), 0);

        valRead = read(sock, buffer, 2048);
        std::cout << "Server: " << buffer << std::endl;
        memset(buffer, 0, sizeof(buffer)); // Clear the buffer
    }

    close(sock);
    return 0;
}