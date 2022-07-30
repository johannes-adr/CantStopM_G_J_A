#include "Button.h"
#include <iostream>
#include "GameWindow.h"
#include <math.h>
#include <iomanip>
#include <unordered_map>


std::string hexStr(const uint8_t *data, int len)
{
    std::stringstream ss;
    ss << std::hex;

    for( int i(0) ; i < len; ++i )
        ss << std::setw(2) << std::setfill('0') << (int)data[i];

    return ss.str();
}


bool Button::animateMouse(sf::RectangleShape &rect, sf::RenderWindow* window, sf::Vector2f offset = {0,0}){
    auto mousePos = sf::Mouse::getPosition(*window);
    auto pos = rect.getPosition();
    pos += offset;
    auto size = rect.getSize();
    if((float)mousePos.x >= pos.x && (float)mousePos.x <= pos.x+size.x + rect.getOutlineThickness() +3){
        if((float)mousePos.y >= pos.y && (float)mousePos.y <= pos.y+size.y + rect.getOutlineThickness() +3) {
            auto corg = rect.getFillColor();
            auto rn = corg.r < 20?0:corg.r-20;
            auto gn = corg.g < 20?0:corg.g-20;
            auto bn = corg.b < 20?0:corg.b-20;
            rect.setFillColor(sf::Color(rn,gn,bn));
            return true;
        }
    }
    return false;
}

Button::Button(std::string text, int fontSize, float xPadd, float yPadd,sf::RectangleShape shape,const sf::Font &font){

    sf::Text t;
    t.setString(text);
    t.setFont(font);
    t.setCharacterSize(fontSize);
    this->text = t;
    this->padding = sf::Vector2f(xPadd,yPadd);
    this->setPosition(0,0);
}


bool Button::gotPressed(){
    if(this->gotpressed){
        this->gotpressed = false;
        return true;
    }
    return false;
}

sf::RectangleShape& Button::getBox(){
    return this->box;
}

Button& Button::setBgColor(sf::Color color) {
    this->box.setFillColor(color);
    return *this;
}

Button& Button::setPosition(float x, float y){
    this->box.setPosition(x,y);
    this->text.setPosition(x + padding.x,y - 4 + padding.y);
    auto textDim = text.getGlobalBounds();

    this->box.setSize(sf::Vector2(textDim.width + padding.x * 2,(float)text.getCharacterSize() + padding.y * 2));
    return *this;
}


sf::Color setOpacity(sf::Color c, int opacity){
    return sf::Color(c.r,c.g,c.b,opacity);
}

void Button::render(SubCanvas &canvas, GameWindow &gameWindow) {

    sf::Color before = this->box.getFillColor();
    auto posBefore = this->box.getPosition();
    bool intersects = Button::animateMouse(this->box,gameWindow.getWindow(),canvas.getOffset());
    auto scaleBefore = this->box.getScale();
    if(intersects){
        this->box.setPosition(posBefore.x-hoverSize/2,posBefore.y-hoverSize/2);

        this->box.scale(1.1,1.1);
    }

    if(opacity < 255){
        if(opacity > 255){
            opacity = 255;
        }
        this->box.setFillColor(setOpacity(this->box.getFillColor(),opacity));
        this->box.setOutlineColor(setOpacity(this->box.getOutlineColor(),opacity));
        this->text.setFillColor(setOpacity(this->text.getFillColor(),opacity));
        opacity+=10;
    }


    bool left = sf::Mouse::isButtonPressed(sf::Mouse::Left);
    if(!this->isPressed && left && intersects){
        this->gotpressed = true;
        this->isPressed = true;
        clickHandler();
    }

    if(!left){
        this->isPressed = false;
    }

    if(intersectedBefore && !intersects){
        mouseLeaveHandler();
    }


    if(!intersectedBefore && intersects){
        mouseEnterHandler();
    }

    canvas.draw(this->box);

    canvas.draw(this->text);
    box.setFillColor(before);
    box.setPosition(posBefore);
    box.setScale(scaleBefore);


    this->intersectedBefore = intersects;
}


Button::Button(): Button("Default") {
}

std::ostream &operator<<(std::ostream &cout, const Button &v) {
    std::string  s2 = v.text.getString();
    return cout << "Button{" << s2 << "}";
}

