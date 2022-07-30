#include "CantStop/Game/Game.h"
#include "CantStop/Game/Dice.h"
#include "CantStop/Player/IPlayer.h"
#include "CantStop/Player/TerminalPlayer/TerminalPlayer.h"
#include "CantStop/Player/Bot/RandomBot.h"
#include "CantStop/Player/Bot/SkippingBot.h"
#include "CantStop/Player/Bot/ScaryBot.h"
#include "CantStop/Player/SFMLPlayer/SFMLPlayer.h"
#include <thread>
#include "JdrTest/Testing.h"
#include "iostream"


/*
 * C++ Projekt DHBW TINF21 - SoSe 2022
 * Marvin Geiger: 8755269
 * Johannes Andrade: 2076690
 */

enum StartMode{
    TestFlow,GUIPlayerVsScaryBot,TerminalPlayerVsScaryBot,GUIPlayerVsTerminalPlayer
};

int main(){
    StartMode mode = StartMode::GUIPlayerVsScaryBot;

    auto game = std::make_shared<Game>();
    if(mode == GUIPlayerVsScaryBot){
        auto p1 = ScaryBot();
        auto p2 = SFMLPlayer(game);
        game->setPlayer(&p2,&p1);
        auto gameThreadRunnable = [game](){
            game->start();
        };
        std::thread gameThread(gameThreadRunnable);
        p2.start();
    }else if(mode == TestFlow){
        auto testing = Test();
        testing.runTests();
    }else if(mode == TerminalPlayerVsScaryBot){
        auto p1 = TerminalPlayer();
        auto p2 = ScaryBot();
        game->setPlayer(&p1,&p2);
        game->start();
    }else if(mode == GUIPlayerVsTerminalPlayer){
        auto p1 = TerminalPlayer();
        auto p2 = SFMLPlayer(game);
        game->setPlayer(&p2,&p1);
        auto gameThreadRunnable = [game](){
            game->start();
        };
        std::thread gameThread(gameThreadRunnable);
        p2.start();
    }
    return 0;
}