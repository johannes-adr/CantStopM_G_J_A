#pragma once
#include "IRenderable.h"
#include "algorithm"
class LambdaRenderable: public IRenderable{
private:
    const std::function<void(SubCanvas &canvas, GameWindow &gameWindow)> lambda;
public:
    explicit LambdaRenderable(std::function<void(SubCanvas &canvas, GameWindow &gameWindow)> lambda);
    void render(SubCanvas &canvas, GameWindow &gameWindow) override;
};


