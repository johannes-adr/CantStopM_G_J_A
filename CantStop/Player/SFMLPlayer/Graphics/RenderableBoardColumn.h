#pragma once

#include "../../../../JdrSFML/JdrSFML.h"
class Game;
class RenderableBoardColumn: public IRenderable {
private:
    const std::shared_ptr<Game> game;
    const int col;
public:
    static constexpr float COL_WIDTH = 50;
    static constexpr float FIELD_HEIGHT = COL_WIDTH;
    static constexpr float COL_WIDTH2 = COL_WIDTH / 2;


    RenderableBoardColumn(std::shared_ptr<Game> game, int col);
    void render(SubCanvas &canvas, GameWindow &gameWindow) override;
};