#include "../../Definitions.h"
#include "Dice.h"
#include "../../Utils/Utils.h"
#include <iostream>
#include <vector>

const DiceCombination Dice::createRandomDiceCombination() {
    constexpr int DICE_COMBINATION_MATRIX[3][4] = {
            0, 1, 2, 3,
            2, 1, 0, 3,
            3, 1, 2, 0
    };
    Array<int, 4> dices{};
    for (int &dice: dices) {
        dice = Utils::genRand(1, 7);
    }

    Array<Vec<int>, 3> combinations{};
    for (int i = 0; i < 3; i++) {
        auto &comb = combinations[i];
        comb.push_back(dices[DICE_COMBINATION_MATRIX[i][0]] + dices[DICE_COMBINATION_MATRIX[i][1]]);
        comb.push_back(dices[DICE_COMBINATION_MATRIX[i][2]] + dices[DICE_COMBINATION_MATRIX[i][3]]);
    }

    Vec<Vec<int>> filteredDuplicates;

    //Go through each combination, look if already in filteredDuplicates, if not, push it (sorted)
    for (auto combination: combinations) {
        bool alreadyIn = false;
        for (auto entry: filteredDuplicates) {
            if (entry.size() == combination.size()) {
                bool isSame =
                        entry[0] == combination[0] && entry[1] == combination[1];            //(6 5) == (6 5) => true
                bool isSameSwapped = entry[0] == combination[1] && entry[1] == combination[0]; //(6 5) == (5 6) => true
                if (isSame || isSameSwapped)alreadyIn = true;
            }
        }
        if (!alreadyIn) {
            std::sort(combination.begin(), combination.end());
            filteredDuplicates.push_back(combination);
        }
    }


    DiceCombination comb{};
    comb.dices = dices;
    comb.combinations = filteredDuplicates;
    return comb;
}

std::ostream &operator<<(std::ostream &cout, const DiceCombination &v) {
    cout << "DiceComb{";
    for (auto dice: v.dices) {
        cout << dice << " ";
    }
    cout << "- ";
    for (auto &comb: v.combinations) {
        cout << "( ";
        for (auto &c: comb) {
            cout << c << " ";
        }
        cout << ")";
    }
    cout << "}";
    return cout;
}


const Array<Array<Array<int, 3>, 3>, 6> Dice::VISUAL_MATRIX{
        //One
        0, 0, 0,
        0, 1, 0,
        0, 0, 0,
        //Two
        0, 0, 1,
        0, 0, 0,
        1, 0, 0,

        //Three
        0, 0, 1,
        0, 1, 0,
        1, 0, 0,

        //Four
        1, 0, 1,
        0, 0, 0,
        1, 0, 1,

        //Five
        1, 0, 1,
        0, 1, 0,
        1, 0, 1,

        //Six
        1, 0, 1,
        1, 0, 1,
        1, 0, 1
};