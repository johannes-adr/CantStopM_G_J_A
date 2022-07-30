#pragma once

#include "../Game/Game.h"
#include <string>
#include <optional>
#include "../Game/Dice.h"
#include "../../Definitions.h"
#include "set"
#include "../../Utils/Utils.h"
typedef Vec<int> SelectedColumns;

class IPlayer {
protected:
    std::string name;
    std::set<int> currentPlayerPosition {};
public:
    IPlayer();
    explicit IPlayer(std::string name);
    void play(Game& game);
    virtual SelectedColumns selectColumns(DiceCombination &combs, Game& game) = 0;
    friend std::ostream & operator<<(std::ostream & cout, IPlayer const & v);
};

