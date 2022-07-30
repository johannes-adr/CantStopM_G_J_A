#include "TerminalPlayer.h"
#include <iostream>
#include "../../Game/Game.h"
SelectedColumns TerminalPlayer::selectColumns(DiceCombination &diceCombination, Game &game) {

    std::cout << "\n" << game << std::endl;
    for(auto dice : diceCombination.dices){
        std::cout << dice << " ";
    }
    std::cout << std::endl;
    int i = 1;
    for(auto& comb : diceCombination.combinations){
        std::cout << i << ") ";

        for(auto dice: comb)std::cout << dice << " ";

        std::cout << std::endl;
        i++;
    }
    std::string input;
    int selectedMove;
    while(true){
        selectedMove = -1;
        std::cout << "Select between 0 - " << diceCombination.combinations.size() << ": ";
        std::getline(std::cin,input);
        try {
            selectedMove = std::stoi(input);
            if(selectedMove <= diceCombination.combinations.size() && selectedMove >= 0){
                break;
            }else{
                std::cerr << "'" << selectedMove << "' has to be in range '" << 0 << "' <= num " << "<= '" << diceCombination.combinations.size() << "'" << std::endl;
            }

        }catch(std::invalid_argument&){
            std::cerr << "Unable to parse '" << input << "' to string" << std::endl;
        }
    }
    SelectedColumns selectedColumns{};
    if(selectedMove == 0)return selectedColumns;
    for(auto num: diceCombination.combinations[selectedMove-1])selectedColumns.push_back(num);
    std::cout << selectedColumns.size();
    return selectedColumns;
}
