#pragma once
#include "SFML/Graphics.hpp"
#include "IRenderable.h"
#include "GameWindow.h"
#include "array"
class Button: public IRenderable{
private:
    bool isPressed = false;
    bool gotpressed = false;
    bool intersectedBefore = false;
    int opacity = 0;

    sf::Text text{};
    sf::Vector2f padding{};
    int hoverSize = 5;
    sf::RectangleShape box{};

public:
    std::function<void()> clickHandler = [](){};
    std::function<void()> mouseEnterHandler = [](){};
    std::function<void()> mouseLeaveHandler = [](){};

    Button(std::string text, int fontSize = 20, float xPadd = 10, float yPadd = 5,sf::RectangleShape shape = sf::RectangleShape{}
            ,const sf::Font &font = GameWindow::getDefaultFont());
    Button();
    Button& setBgColor(sf::Color color);

    Button& setPosition(float x, float y);
    sf::RectangleShape& getBox();
    bool gotPressed();
    void render(SubCanvas &canvas, GameWindow &gameWindow) override;
    friend std::ostream &operator<<(std::ostream &cout, const Button &v);
    static bool animateMouse(sf::RectangleShape &rect, sf::RenderWindow* window, sf::Vector2f offset);
};
