#include <iostream>
#include <SFML/Network.hpp>
#include "ChatBox.hpp"

class Client {
private:
    sf::IpAddress ip = sf::IpAddress::getLocalAddress();
    sf::IpAddress tempIp;
    sf::IpAddress serverIp;
    sf::UdpSocket socket;
    std::string text;
    char buffer[2000];
    unsigned short tempPort;
    unsigned short port;
    std::string sIp;
    char c;
    std::string name;
    sf::Packet packet;

public:
    Client();
    ~Client() = default;
    // refactor the way it receives messages
    void sendMessage (std::string message);
    void connectToServer (sf::IpAddress serverIp);
    bool receiveMessages ();

    std::string getMessage ();

    void setName (std::string name);
    void disconnect ();
};

void Client::setName (std::string name) {
    this->name = name;
}

Client::Client() {
    socket.bind(socket.AnyPort, ip);
    socket.setBlocking(false);
}

void Client::connectToServer(sf::IpAddress sIp) {
    serverIp = sIp;
    packet << name;
    socket.send(packet, serverIp, 2000);
}

void Client::sendMessage(std::string message) {
    packet << message;
    socket.send(packet, serverIp, 2000);
} 

bool Client::receiveMessages () {
    socket.receive(packet, tempIp, tempPort);
    if (!packet.endOfPacket())
        return true;
    return false;
}

std::string Client::getMessage() {
    std::string tempName;
    std::string tempMessage;
    packet >> tempName >> tempMessage;
    return tempName + ": " + tempMessage;
}

void Client::disconnect () {
    socket.send("", 1, serverIp, 2000);
}