#include <iostream>
#include <SFML/Network.hpp>
#include <thread>
#include <conio.h>

sf::IpAddress ip = sf::IpAddress::getLocalAddress();
sf::IpAddress tempIp;
sf::IpAddress serverIp;
sf::UdpSocket socket;
std::string text;
size_t received;
unsigned short tempPort;
unsigned short port;
std::string sIp;
char buffer[2000];
char c;
std::string name;


void receiveData () {
    while (true) {
        socket.receive(buffer, sizeof(buffer), received, tempIp, tempPort);
        if (received>0)
            std::cout << buffer << std::endl;
    }
}

int main () {
    std::cout << "Enter IP to connect to: ";
    while (true) {
        c = (char)getch();
        if (c==13)
            break;
        sIp+=c;
        std::cout << "*";
    }
    serverIp = sIp;
    std::cout << "\nEnter Name: ";
    socket.bind(socket.AnyPort, ip);
    std::thread receiveThread(receiveData);

    // std::cin.ignore();
    std::getline(std::cin, name);
    socket.send(name.c_str(), name.length()+1, serverIp, 2000);

    while (true) {
        std::getline(std::cin, text);
        text = name + ": " + text;
        socket.send(text.c_str(), text.length()+1, serverIp, 2000);
    }
}
