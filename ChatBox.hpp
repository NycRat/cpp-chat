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
            allMessages[e]->setPosition({0,tempDown});
            allMessages[e]->setFillColor(sf::Color::White);
            target.draw(*allMessages[e], states);
            tempDown += (float)fontSize*1.5;
            if (tempDown>=height-50) {
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
public:
    ChatBox(/* args */);
    ChatBox(unsigned int width, unsigned int height, sf::Font font, unsigned int fontSize);
    ~ChatBox() = default;
    void moveText (float dis);
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

void ChatBox::moveText (float dis) {

}

void ChatBox::addText (std::string message) {
    allMessages.push_back(new sf::Text(message, font, 22));
}

#endif