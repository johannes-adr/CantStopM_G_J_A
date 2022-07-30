#include "GameBackground.h"
#include "ColorScheme.h"
GameBackground::GameBackground() {
    zIndex = -1;
}

void GameBackground::render(SubCanvas &canvas, GameWindow &gameWindow) {
    auto winSize = gameWindow.getWindow()->getSize();
    sf::RectangleShape rect{};
    rect.setSize(sf::Vector2f(winSize.x,winSize.y));
    canvas.draw(rect);
}

