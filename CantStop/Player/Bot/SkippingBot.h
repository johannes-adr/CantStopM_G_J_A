#pragma once
#include "Bot.h"
class SkippingBot: public Bot{
    SelectedColumns selectColumns(DiceCombination &combs, Game &game) override;
};