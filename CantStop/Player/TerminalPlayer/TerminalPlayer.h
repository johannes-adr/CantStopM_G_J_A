#pragma once
#include "../IPlayer.h"
#include "../../Game/Game.h"
class TerminalPlayer: public IPlayer{
public:
    SelectedColumns selectColumns(DiceCombination &combs, Game& game) override;
};


