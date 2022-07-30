#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics.hpp>
#include "SubCanvas.h"
#include <iostream>

SubCanvas::SubCanvas(float x, float y,sf::RenderWindow* window) : x(
        x), y(y), window(window) {}


SubCanvas& SubCanvas::newSubCanvas(float x, float y) {
    auto subCanvas = new SubCanvas{this->x+x,this->y+y,this->window};
    subCanvas->zIndex = this->zIndex+1;
    this->addRenderable(subCanvas);
    return *subCanvas;
}

SubCanvas SubCanvas::disconnectedSubCanvas(float x, float y) {
    auto subCanvas = SubCanvas{this->x+x,this->y+y,this->window};
    subCanvas.zIndex = this->zIndex+1;
    return subCanvas;
}

bool comparePtrToNode(IRenderable* a, IRenderable* b) {
    return (*a).getZIndex() < (*b).getZIndex();
}

void SubCanvas::addRenderable(IRenderable *renderable) {
    this->renderables.push_back(renderable);
    std::stable_sort(this->renderables.begin(), this->renderables.end(), comparePtrToNode);
}


void SubCanvas::render(SubCanvas& canvas, GameWindow &game) {
    for (auto item : this->renderables) {
        item->render(*this, game);
    }
}

void SubCanvas::renderOnSFML(const sf::RenderWindow& window, GameWindow& game){
    for (auto item : this->renderables) {
        item->render(*this, game);
    }
}

sf::Vector2f SubCanvas::getOffset() const {
    return sf::Vector2f{x,y};
}

SubCanvas::~SubCanvas() {
    for(auto rends : renderables){
        delete rends;
    }
}

