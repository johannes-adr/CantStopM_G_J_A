#pragma once
#include "../../../../JdrSFML/JdrSFML.h"
class GameBackground: public IRenderable{
public:
    GameBackground();
    void render(SubCanvas& canvas,GameWindow& gameWindow) override;
};