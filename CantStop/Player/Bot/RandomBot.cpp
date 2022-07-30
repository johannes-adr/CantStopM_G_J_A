#include "RandomBot.h"
#include "iostream"
SelectedColumns RandomBot::selectColumns(DiceCombination &combs, Game &game) {
    int comb = Utils::genRand(0,combs.combinations.size());
    int skipProbability = Utils::genRand(0,4);
    if(skipProbability==0){
        return {};
    }
    return combs.combinations[comb];
}
