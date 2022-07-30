#include "ScaryBot.h"

SelectedColumns ScaryBot::selectColumns(DiceCombination &combs, Game &game) {
    if(this->currentPlayerPosition.size() >= 3){
        return {};
    }
    return combs.combinations[0];
}
