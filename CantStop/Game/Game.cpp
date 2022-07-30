#include "Game.h"
#include <iostream>
#include "../Player/IPlayer.h"
#include "../../Utils/Utils.h"
#include "../../Definitions.h"

#define PLAYER_1_CHECKPOINT C_BLUE;
#define PLAYER_1_PROGRESS C_CYAN
#define PLAYER_2_CHECKPOINT C_RED
#define PLAYER_2_PROGRESS C_MAGENTA

void Game::setPlayer(IPlayer *p1, IPlayer *p2) {
    this->player[0] = p1;
    this->player[1] = p2;
    currentPlayer = p1;
}

int Game::update(){
    Expect_NotNull(this->currentPlayer);
    exceptPlayerId(*this->currentPlayer);
    currentPlayer->play(*this);
    this->currentPlayer = this->currentPlayer == this->player[0] ? this->player[1] : this->player[0];

    int p1WonCol = 0;
    int p2WonCol = 0;
    for(auto& col : columns){
        if(col.playerProgress[0].checkPoint >= col.height){
            p1WonCol++;
        }
        if(col.playerProgress[1].checkPoint >= col.height){
            p2WonCol++;
        }
    }
    if(p1WonCol == 3)return 1;
    if(p2WonCol == 3)return 2;
    return 0;

}



void Game::start() {
    std::cout << "Game start" << std::endl;
    for(auto& p : player){
        if(p == nullptr){
            std::cout << C_RED << "Unable to start game - player(s) not set" << C_RESET;
            std::exit(-1);
        }
    }
    this->isRunning = true;
    while(this->isRunning){
        int result = this->update();
        if(result != 0){
            std::cout << "Player " << result << " won!!" << std::endl;
            break;
        }
    }

}

void Game::stop() {
    this->isRunning = false;
}

Game::Game() {
    int i =0;
    for(auto& col : this->columns){
        // 2 4 6 8 12 8 6 4 2 für COLLUMNS_AMOUNT = 11
        auto num = (i <= COLUMNS_AMOUNT / 2) ?
                   (i * 2 + 2) :
                   (COLUMNS_AMOUNT - (i - COLUMNS_AMOUNT / 2) * 2 + 1);
        col.height = num;
        i++;
    }
}

std::ostream &operator<<(std::ostream &cout, const Game &v) {
    for(int i =0;i < 12;i++){
        for(auto col: v.columns){
           if(col.height > i){
                if(col.playerProgress[0].checkPoint > i){
                    cout << PLAYER_1_CHECKPOINT;
                }else if(col.playerProgress[0].fieldProgress > i){
                    cout << PLAYER_1_PROGRESS;
                }
                cout << "#" << C_RESET;

                if(col.playerProgress[1].checkPoint > i){
                    cout << PLAYER_2_CHECKPOINT;
                }else if(col.playerProgress[1].fieldProgress > i){
                    cout << PLAYER_2_PROGRESS;
                }
                cout << "#" << C_RESET;
            }else{
                cout << "  ";
            }
        }
        cout << std::endl;
    }
    return cout;
}

void printTeam(std::ostream &cout, const PlayerProgress &p, int height, std::string color) {
    for (int i = 0;i < height;i++) cout << color << "[■]" << C_RESET;
}

void Game::loadBoard(std::string board){
    Vec<std::string> parts = Utils::splitStr(board,' ');
    zip(parts,columns,[](std::string& colData,Column& column){
        Vec<std::string> teams = Utils::splitStr(colData,'.');
        zip(teams,column.playerProgress,[](std::string& s, PlayerProgress& playerProgress){
            Vec<std::string> parts = Utils::splitStr(s,',');
            playerProgress.checkPoint = std::stoi(parts[0]);
            playerProgress.fieldProgress = std::stoi(parts[1]);
        });
    });

}

Array<Column, Game::COLUMNS_AMOUNT> Game::getColumnsCopy() {
    return this->columns;
}

/**
 * @return {if not found? -1 : x∈N}
 */
int Game::getPlayerId(IPlayer const& pl){
    for(int i = 0;i < player.size();i++)if(player[i] == &pl)return i;
    return -1;
}

/**
 * @return {if not found? !!EXCEPTION!! : x∈N}
 */
int Game::exceptPlayerId(IPlayer const& pl){
    int id = getPlayerId(pl);
    if(id == -1)throw std::logic_error("given Player not in game");
    return id;
}

/**
 * Set checkPoint = fieldProgress for each Column
 */
void Game::savePlayerProgression(IPlayer const& pl) {
    int id = exceptPlayerId(pl);
    for(auto& col: columns){
        auto& pgress = col.playerProgress[id];
        pgress.checkPoint = pgress.fieldProgress;
    }
}

/**
 * Set progress for SelectedColumns by pl
 */



void Game::doProgress(SelectedColumns & selCols, IPlayer const& pl){
    int id = exceptPlayerId(pl);
    for(auto const& selCol : selCols){
        columns[selCol].playerProgress[id].fieldProgress++;
    }
}

/**
 * Set fieldProgess = checkPoint for each Column
 */
void Game::discardPlayerProgression(IPlayer const& player) {
    int id = exceptPlayerId(player);
    for(auto& col: columns){
        auto& pgress = col.playerProgress[id];
        pgress.fieldProgress = pgress.checkPoint;
    }
}

IPlayer *Game::getCurrentPlayer() const {
    return currentPlayer;
}

/*
 * =======
 * TO_STRING
 * =======
 */
std::ostream &operator<<(std::ostream &cout, const Column &v) {
    cout << C_RESET << "(" << C_RED << v.playerProgress[0]

    << C_RESET << "^" << std::to_string(v.height) << "^"

    << C_YELLOW << v.playerProgress[1] << C_RESET << ") ";
    return cout;
}

std::ostream &operator<<(std::ostream &cout, const PlayerProgress &v) {
    return cout << std::to_string(v.checkPoint) << "|" << std::to_string(v.fieldProgress);
}


/*
 * =======
 * EQUALS
 * =======
 */
bool operator==(const PlayerProgress& a, const PlayerProgress& b)
{
    return a.fieldProgress == b.fieldProgress && a.checkPoint == b.checkPoint;
}

bool operator==(const Column& a, const Column& b)
{
    return a.height == b.height && a.playerProgress == b.playerProgress;
}