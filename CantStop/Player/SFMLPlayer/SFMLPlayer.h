#pragma once
#include "../IPlayer.h"
#include "../../../JdrSFML/JdrSFML.h"
#include "Graphics/RenderableDice.h"


class SFMLPlayer: public IPlayer{
private:
    GameWindow* win;
    std::shared_ptr<Game> game;
    Vec<std::pair<Button,Vec<int>>> chooseDiceButtons{};
    Vec<RenderableDice> currentDices;
public:
    SFMLPlayer(const std::shared_ptr<Game>& game);
    ~SFMLPlayer();
    SelectedColumns selectColumns(DiceCombination &combs, Game &game) override;

    void start();

    Button* btnSkip;
};

