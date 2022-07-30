#pragma once
#include "../../../../JdrSFML/JdrSFML.h"
class Game;
class IPlayer;

class OnTurnDisplay: public IRenderable{
private:
    const std::shared_ptr<Game> game;
    const IPlayer *player;
public:
    OnTurnDisplay(std::shared_ptr<Game> game, IPlayer *player);
    void render(SubCanvas &canvas, GameWindow &gameWindow) override;


};


