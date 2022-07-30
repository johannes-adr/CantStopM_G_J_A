#pragma once

#include <SFML/Graphics.hpp>
#include "../IRenderable.h"
#include "../../Definitions.h"

class SubCanvas: public IRenderable{
private:
    float x, y;
    sf::RenderWindow *window = nullptr;
    Vec<IRenderable*> renderables{};

public:
    SubCanvas(float x, float y, sf::RenderWindow *window);
    SubCanvas& newSubCanvas(float x, float y);
    void addRenderable(IRenderable* renderable);

    virtual void render(SubCanvas& canvas, GameWindow& gameWindow) override;
    void renderOnSFML(const sf::RenderWindow& window, GameWindow& game);
    sf::Vector2f getOffset() const;
    template<typename T>void draw(T &drawable);
    ~SubCanvas() override;

    SubCanvas disconnectedSubCanvas(float x, float y);
};


template<typename T> void SubCanvas::draw(T& drawable){
    auto posBefore = drawable.getPosition();
    auto newPos = posBefore;
    newPos.x += this->x;
    newPos.y += this->y;

    drawable.setPosition(newPos);
    (*this->window).draw(drawable);
    drawable.setPosition(posBefore);
}