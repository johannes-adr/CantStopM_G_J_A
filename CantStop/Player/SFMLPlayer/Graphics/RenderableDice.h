#pragma once
#include "../../../../JdrSFML/JdrSFML.h"
#include "../../../Game/Dice.h"
class RenderableDice: public IRenderable{
private:
    const int dice;
    const int size;
public:
    RenderableDice(const int dice, const int size);
    void render(SubCanvas &canvas, GameWindow &gameWindow) override;
};


