#include <iostream>
#include <SFML/Network.hpp>

int main () {
    sf::IpAddress ip = sf::IpAddress::getLocalAddress();
    sf::IpAddress serverIp;
    sf::UdpSocket socket;
    char buffer[2000];
    std::string text;
    size_t received;

    socket.bind(2002, ip);
    sf::IpAddress tempIp;
    unsigned short tempPort;

    while (true) {
        socket.receive(buffer, sizeof(buffer), received, tempIp, tempPort);
        if (received>0)
            std::cout << buffer << std::endl;
    }
}