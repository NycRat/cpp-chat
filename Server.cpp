#include <SFML/Network.hpp>
#include <iostream>

int main () {
    sf::IpAddress serverIp = sf::IpAddress::getLocalAddress();
    sf::UdpSocket socket;
    char buffer[2000];
    std::map<unsigned short, sf::IpAddress> computerId;
    size_t received;

    socket.bind(2000, serverIp);
    sf::IpAddress tempIp;
    unsigned short tempPort;
    std::string ease;
    char showIP = 'n';

    std::cout << "Show IP Address? (y/n)  ";
    std::cin >> showIP;
    if (showIP == 'y') {
        std::cout << "Server IP: " << serverIp << std::endl;
    }

    while (true) {
        socket.receive(buffer, sizeof(buffer), received, tempIp, tempPort);
        if (computerId.count(tempPort) == 0) {
            std::cout << "NEW CONNECTION\n";
            computerId[tempPort] = tempIp;
        } else {
            std::cout << buffer << std::endl;
            for (auto id : computerId) {
                if (id.first != tempPort) // || id.second != tempIp)
                    socket.send(buffer, sizeof(buffer), id.second, id.first);
            }
        }
    }
}