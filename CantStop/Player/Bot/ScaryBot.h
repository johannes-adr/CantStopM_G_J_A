#pragma once
#include "Bot.h"
class ScaryBot: public Bot{
    SelectedColumns selectColumns(DiceCombination &combs, Game &game) override;
};


