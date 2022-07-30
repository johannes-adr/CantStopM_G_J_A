#include "LambdaRenderable.h"

#include <utility>
#include "iostream"
LambdaRenderable::LambdaRenderable(std::function<void(SubCanvas &canvas, GameWindow &gameWindow)> lambda): lambda(std::move(lambda)) {}

void LambdaRenderable::render(SubCanvas &canvas, GameWindow &gameWindow) {
    lambda(canvas,gameWindow);
}
