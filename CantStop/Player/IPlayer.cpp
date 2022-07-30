#include "IPlayer.h"
#include <iostream>
#include <utility>
void IPlayer::play(Game& game) {

    currentPlayerPosition.clear();
    while (true){
        auto colCopy = game.getColumnsCopy();
        DiceCombination dc = Dice::createRandomDiceCombination();
        Vec<Vec<int>> filteredCombs;
        for(int i = 0;i < dc.combinations.size(); i++){
            Vec<int> ncomb;
            auto comb = dc.combinations[i];
            for(int j = 0;j < comb.size();j++){
                int num = comb[j];
                //Tut uns leid, dass er bei .size() == 2 die Kombination nicht aufsplittet :(
                if(currentPlayerPosition.size() < 3 || Utils::vecContains(currentPlayerPosition,num)){
                    ncomb.push_back(num);
                }
            }
            if(!ncomb.empty()){
                filteredCombs.push_back(ncomb);
            }
        }


        Vec<Vec<int>> heightFilteredCombs;
        for(auto& combination : filteredCombs){
            Vec<int> filtComb;
            for(int num : combination){
               auto& col = colCopy[num-2];
               //Problem: bei doppeltem column kann die höhe überschritten werden...
               if(col.playerProgress[game.getPlayerId(*this)].fieldProgress < col.height){
                    filtComb.push_back(num);
               }
            }
            if(!filtComb.empty()){
                heightFilteredCombs.push_back(filtComb);
            }
        }
        if(heightFilteredCombs.empty()){
            game.discardPlayerProgression(*this);
            break;
        }
        dc.combinations =heightFilteredCombs;

        SelectedColumns selected = this->selectColumns(dc, game);
        auto cpy = currentPlayerPosition;
        if(currentPlayerPosition.size() > 3){
            currentPlayerPosition = cpy;
        }

        for(auto& col : selected){
            col-=2;
        }

        if(selected.empty()){
            game.savePlayerProgression(*this);
            break;
        }else{
            for(auto s : selected)this->currentPlayerPosition.insert(s+=2);
            game.doProgress(selected,*this);
        }
    }
}

std::ostream &operator<<(std::ostream &cout, const IPlayer &v) {
    return cout << "IPlayer{" << v.name << "}";
}

IPlayer::IPlayer(): name("Default") {}

IPlayer::IPlayer(std::string name): name(std::move(name)) {}
