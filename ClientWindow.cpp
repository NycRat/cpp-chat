#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Client.hpp"

class ClientWindow: public sf::RenderWindow {
private:
    void run ();
    void render ();
    std::string text;
    sf::Font font;
    sf::Text enterText;
    sf::IpAddress serverIp = sf::IpAddress::getLocalAddress();
    Client client {};
    std::string receivedText;
    std::string name;
    ChatBox chatBox{};
public:
    ClientWindow();
    ~ClientWindow() = default;
};

ClientWindow::ClientWindow() {
    // std::cout << "IP: ";
    // std::cin >> text;
    std::cout << "Name: ";
    // std::cin.ignore();
    getline(std::cin, name);
    // serverIp = text;
    client.setName(name);
    client.connectToServer(serverIp);
    text="";
    create({1200, 800}, "Chat", sf::Style::Titlebar | sf::Style::Close);
    sf::Image winIcon;
    winIcon.loadFromFile("chatIcon.jpg");
    setIcon(300,300,winIcon.getPixelsPtr());
    font.loadFromFile("JetBrainsMono.ttf");
    enterText.setFont(font);
    enterText.setCharacterSize(22);
    enterText.setFillColor(sf::Color::White);
    enterText.setPosition({0, (float)getSize().y-enterText.getLocalBounds().height});
    chatBox.initialize(getSize().x, getSize().y, font, 18);
    run();
}

void ClientWindow::run () {
    sf::Event ev;
    requestFocus();
    chatBox.addText("Enter Name: ");
    while (isOpen()) {
        while (pollEvent(ev)) {
            if (ev.type == sf::Event::Closed)
                close();
            if (ev.type == sf::Event::TextEntered) {
                if (ev.text.unicode < 127) {
                    if (ev.text.unicode != '\b' && ev.text.unicode != '\n' && ev.text.unicode != 13) {
                        text += (static_cast<char>(ev.text.unicode));
                    }
                }
            }
            if (ev.type == sf::Event::KeyPressed) {
                switch (ev.key.code) {
                    case sf::Keyboard::Enter:
                        if (text!="") {
                            client.sendMessage(text);
                            chatBox.addText(name + ": " + text);
                            std::cout << name << ": " << text << std::endl;
                            text="";
                        }
                        break;
                    case sf::Keyboard::BackSpace:
                        text.pop_back();
                        break;
                    case sf::Keyboard::Escape:
                        close();
                        break;
                }
            }
        }
        if (client.receiveMessages()) {
            receivedText = client.getMessage();
            chatBox.addText(receivedText);
            std::cout << receivedText << std::endl;
        }

        enterText.setString(text);
        enterText.setPosition({0, (float)getSize().y-10-enterText.getLocalBounds().height});
        if (enterText.getLocalBounds().width >= getSize().x) {
            text += text.back();
            text.at(text.length()-2) = '\n';
        }

        render();
    }
    client.disconnect();
}

void ClientWindow::render () {
    clear();
    draw(chatBox);
    draw(enterText);
    display();
}

int main () {
    ClientWindow window{};
}