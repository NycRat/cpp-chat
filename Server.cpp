#include <SFML/Network.hpp>
#include <iostream>

class userData {
public:
    userData(sf::IpAddress i, std::string s): ip(i), name(s) {};
    ~userData() = default;
    sf::IpAddress ip;
    std::string name;
};


int main () {
    sf::Packet sendPacket;
    sf::Packet receivePacket;
    sf::IpAddress serverIp = sf::IpAddress::getLocalAddress();
    sf::UdpSocket socket;
    std::map<unsigned short, userData*> connectedUsers;
    std::string temp;

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
        socket.receive(receivePacket, tempIp, tempPort);
        receivePacket >> temp;
        std::cout << "Received from: " << tempIp << " " << tempPort << std::endl << temp << std::endl;
        if (connectedUsers.count(tempPort) == 0 && tempPort != 0) { // New Connected User
            std::cout << "NEW CONNECTION\nIP: " << tempIp << "\nPORT: " << tempPort << "\n" << "NAME: " << temp << "\n";
            // socket.send("Connected Users:\n", 18, tempIp, tempPort);
            sendPacket << "New User Connected" << temp;
            for (auto id : connectedUsers) {
                if (id.first != tempPort) // || id.second != tempIp)
                    socket.send(sendPacket, id.second->ip, id.first);
                sendPacket.clear();
                sendPacket << id.second->name;
                socket.send(sendPacket, tempIp, tempPort);
                sendPacket << "New User Connected: " << temp;
            }
            connectedUsers[tempPort] = new userData(tempIp, temp);
        } else { // New message from connected user
            if (temp == "\0") { // figure out the packet things
                std::cout << tempPort << " Has Disconnected" << std::endl;
                connectedUsers.erase(tempPort);
            } else {
                if (temp != "") {
                    sendPacket << connectedUsers[tempPort]->name << temp;
                    std::cout << connectedUsers[tempPort]->name << ": " << temp << std::endl;
                    for (auto id : connectedUsers) {
                        if (id.first != tempPort) {
                            socket.send(sendPacket, id.second->ip, id.first);
                            std::cout << "Sent to: "  << id.second->ip<< " " << id.first << std::endl;
                        }
                    }
                }
            }
        }
        receivePacket.clear();
        sendPacket.clear();
        temp = "";
    }
}