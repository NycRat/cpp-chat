#include <SFML/Graphics.hpp>
#include <vector>

#ifndef CHATBOX_HPP
#define CHATBOX_HPP

class ChatBox: public sf::Drawable {
private:
    std::vector <sf::Text*> allMessages;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        float tempDown = 0;
        for (int e=0; e<allMessages.size(); e++) {
            allMessages[e]->setPosition({0,tempDown-offset});
            allMessages[e]->setFillColor(sf::Color::White);
            target.draw(*allMessages[e], states);
            tempDown += (float)fontSize*1.5;
            if (tempDown-offset>=height-50) {
                break;
            }
        }
        // target.draw(somethign, states);
    };
    sf::Font font;
    unsigned int fontSize;

    unsigned int width;
    unsigned int height;
    unsigned int maxLines;

    int offset=0;

public:
    ChatBox(/* args */);
    ChatBox(unsigned int width, unsigned int height, sf::Font font, unsigned int fontSize);
    ~ChatBox() = default;
    void moveText (int dir);
    void addText (std::string message);
    void initialize (unsigned int width, unsigned int height, sf::Font font, unsigned int fontSize);
};

ChatBox::ChatBox() {
}

ChatBox::ChatBox (unsigned int width, unsigned int height, sf::Font font, unsigned int fontSize) {
    this->width = width;
    this->height = height;
    this->font = font;
    this->fontSize = fontSize;
    maxLines = height/fontSize*1.5;
}

void ChatBox::initialize(unsigned int width, unsigned int height, sf::Font font, unsigned int fontSize) {
    this->width = width;
    this->height = height;
    this->font = font;
    this->fontSize = fontSize;
}

void ChatBox::moveText (int dir) {
    if (dir == 1) { // scroll up
        if (offset > 0) {
            offset -= fontSize * 1.5 * dir;
        }
    }
    if (dir == -1) { // scroll down
        if (offset+fontSize*1.5*dir <= (allMessages.size()*fontSize*1.5 - height)) {
            offset -= fontSize * 1.5 * dir;
        }
    }
}

void ChatBox::addText (std::string message) {
    std::cout << offset << " " << allMessages.size()*fontSize*1.5 - height << std::endl;
    if (offset <= allMessages.size()*fontSize*1.5 - (height - 50)) {
        offset += fontSize * 1.5;
    }
    allMessages.push_back(new sf::Text(message, font, 22));
}

#endif