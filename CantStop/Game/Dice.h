#pragma once
#include <vector>
#include <optional>
#include "../../Definitions.h"
typedef Vec<int> Combination;
class DiceCombination{
public:
    Array<int,4> dices;
    Vec<Combination> combinations;

    friend std::ostream & operator<<(std::ostream & cout, DiceCombination const & v);
};

class Dice {
public:
    const static DiceCombination createRandomDiceCombination();
    const static Array<Array<Array<int, 3>, 3>, 6> VISUAL_MATRIX;
};


