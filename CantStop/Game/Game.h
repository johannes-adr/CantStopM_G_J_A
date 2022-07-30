#pragma once
class IPlayer;
#include "../../Definitions.h"

class PlayerProgress{
public:
    int checkPoint = 0;
    int fieldProgress = 0;
    friend std::ostream & operator<<(std::ostream & cout, PlayerProgress const & v);
    friend bool operator==(const PlayerProgress& a, const PlayerProgress& b);
};

class Column{
public:
    Array<PlayerProgress,2> playerProgress{};
    int height = 0;
    friend std::ostream & operator<<(std::ostream & cout, Column const & v);
    friend bool operator==(const Column& a, const Column& b);
};

class Game {
public:
    static constexpr int COLUMNS_AMOUNT = 11;

    explicit Game();
    virtual void start();
    virtual void stop();
    void setPlayer(IPlayer *p1, IPlayer *p2);
    friend std::ostream & operator<<(std::ostream & cout, Game const & v);
    void loadBoard(std::string board);
    void savePlayerProgression(IPlayer const& pl);
    void discardPlayerProgression(IPlayer const& player);
    IPlayer *getCurrentPlayer() const;
    int getPlayerId(IPlayer const& pl);
    void doProgress(Vec<int> &columns, const IPlayer &pl);
    Array<Column,Game::COLUMNS_AMOUNT> getColumnsCopy();
    virtual int update();

protected:
    bool isRunning = false;
    Array<Column,COLUMNS_AMOUNT> columns{};
    Array<IPlayer*,2> player{};
    IPlayer* currentPlayer{};
    int exceptPlayerId(const IPlayer &pl);
};

