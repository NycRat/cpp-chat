#include <iostream>
#include <SFML/Network.hpp>
#include <conio.h>
#include <thread>


sf::IpAddress ip = sf::IpAddress::getLocalAddress();
sf::IpAddress tempIp;
sf::IpAddress serverIp;
sf::UdpSocket socket;
std::string text;
size_t received;
unsigned short tempPort;
unsigned short port;
std::string sIp;
std::string name;
char buffer[2000];
char c;


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
    ip = sIp;
    std::cout << "\nEnter Port: ";
    std::cin >> port;
    socket.bind(port, ip);
    std::cout << "Enter Name: ";
    std::cin >> name;
    serverIp = text;
    text = "";

    std::thread receiveThread(receiveData);

    while (true) {
        std::getline(std::cin, text);
        text = name + ": " + text;
        socket.send(text.c_str(), text.length()+1, serverIp, 2000);
    }
}
